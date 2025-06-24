#include "hash.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

PlayerHashTable::PlayerHashTable(int size, CollisionMethod method)
    : tableSize(size), elementCount(0), collisionCount(0), collisionMethod(method),
      chainingTable(method == CollisionMethod::CHAINING ? size : 0),
      probingTable(method == CollisionMethod::LINEAR_PROBING ? size : 0)
{
}

int PlayerHashTable::computeHashIndex(long long key) const
{
    return key % tableSize;
}

void PlayerHashTable::loadPlayersFromCSV(const string &filePath)
{
    ifstream file(filePath);
    string line;

    getline(file, line);
    while (getline(file, line))
    {
        stringstream ss(line);
        string idStr, country, created;
        getline(ss, idStr, ',');
        getline(ss, country, ',');
        getline(ss, created, ',');

        if (!idStr.empty())
        {
            long long id = stoll(idStr);
            insertPlayer(Player(id, country, created));
        }
    }
}

void PlayerHashTable::insertPlayer(Player p)
{
    int index = computeHashIndex(p.playerId);

    if (collisionMethod == CollisionMethod::CHAINING)
    {
        Player *existing = chainingTable[index].search(p.playerId);
        if (existing)
        {
            *existing = p;
        }
        else
        {
            if (!chainingTable[index].isEmpty())
                collisionCount++;

            chainingTable[index].insert(p);
            elementCount++;
        }
    }
    else
    {
        int startIndex = index;
        int probeCount = 0;
        while (probingTable[index].state == EntryState::OCCUPIED)
        {
            if (probingTable[index].player.playerId == p.playerId)
            {
                probingTable[index].player = p;
                return;
            }
            index = (index + 1) % tableSize;
            probeCount++;
            if (index == startIndex)
                return;
        }

        probingTable[index].player = p;
        probingTable[index].state = EntryState::OCCUPIED;
        elementCount++;

        if (probeCount > 0)
            collisionCount++;
    }
}

Player *PlayerHashTable::findPlayerById(long long id)
{
    int index = computeHashIndex(id);
    if (collisionMethod == CollisionMethod::CHAINING)
    {
        return chainingTable[index].search(id);
    }
    else
    {
        int startIndex = index;
        while (probingTable[index].state != EntryState::EMPTY)
        {
            if (probingTable[index].state == EntryState::OCCUPIED &&
                probingTable[index].player.playerId == id)
            {
                return &probingTable[index].player;
            }
            index = (index + 1) % tableSize;
            if (index == startIndex)
                break;
        }
        return nullptr;
    }
}

bool PlayerHashTable::removePlayerById(long long id)
{
    int index = computeHashIndex(id);
    if (collisionMethod == CollisionMethod::CHAINING)
    {
        if (chainingTable[index].remove(id))
        {
            elementCount--;
            return true;
        }
    }
    else
    {
        int startIndex = index;
        while (probingTable[index].state != EntryState::EMPTY)
        {
            if (probingTable[index].state == EntryState::OCCUPIED &&
                probingTable[index].player.playerId == id)
            {
                probingTable[index].state = EntryState::DELETED;
                elementCount--;
                return true;
            }
            index = (index + 1) % tableSize;
            if (index == startIndex)
                break;
        }
    }
    return false;
}

void PlayerHashTable::exibirEstatisticas() const
{
    cout << "\n=== ESTATISTICAS ===" << endl;
    cout << "Tamanho da tabela: " << tableSize << endl;
    cout << "Elementos armazenados: " << elementCount << endl;
    cout << "Fator de carga: " << (float)elementCount / tableSize << endl;
    cout << "Numero de colisoes: " << collisionCount << endl;
}
