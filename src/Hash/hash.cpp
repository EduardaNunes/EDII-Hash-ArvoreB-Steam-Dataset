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
            if ((float)elementCount / tableSize > 0.7f)
            {
                rehash();
            }
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
        if ((float)elementCount / tableSize > 0.7f)
        {
            rehash();
        }

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

void PlayerHashTable::rehash() {
    int newSize = nextPrime(tableSize * 2);

    if (collisionMethod == CollisionMethod::CHAINING) {
        vector<LinkedList<Player>> newTable(newSize);
        for (auto &list : chainingTable) {
            Node<Player>* current = list.getHead();
            while (current) {
                int newIndex = current->data.playerId % newSize;
                newTable[newIndex].insert(current->data);
                current = current->next;
            }
        }
        chainingTable = move(newTable);
    } else {
        vector<HashEntry> newTable(newSize);
        for (auto &entry : probingTable) {
            if (entry.state == EntryState::OCCUPIED) {
                int newIndex = entry.player.playerId % newSize;
                while (newTable[newIndex].state == EntryState::OCCUPIED) {
                    newIndex = (newIndex + 1) % newSize;
                }
                newTable[newIndex].player = entry.player;
                newTable[newIndex].state = EntryState::OCCUPIED;
            }
        }
        probingTable = move(newTable);
    }

    tableSize = newSize;
    collisionCount = 0;  // Recalcular se necessário
}

bool PlayerHashTable::isPrime(int number) {
    if (number <= 1) return false;
    if (number == 2) return true;
    if (number % 2 == 0) return false;
    for (int i = 3; i * i <= number; i += 2)
        if (number % i == 0) return false;
    return true;
}

int PlayerHashTable::nextPrime(int number) {
    while (!isPrime(number)) number++;
    return number;
}
