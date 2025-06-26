#include "hash.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

Hash::Hash(int size, CollisionMethod m)
    : tableSize(size), numElements(0), numCollisions(0), method(m)
{
    if (method == CHAINING)
    {
        chainTable.resize(tableSize);
    }
    else
    {
        openTable.resize(tableSize);
    }
}

int Hash::hashFunction(long long key) const
{
    return key % tableSize;
}

void Hash::loadPlayers(const string &filePath)
{
    ifstream file(filePath);
    string line;

    getline(file, line); // ignora o cabeçalho
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
            insert(Player(id, country, created));
        }
    }
}

void Hash::insert(Player p)
{
    int idx = hashFunction(p.playerId);

    if (method == CHAINING)
    {
        Player *existing = chainTable[idx].search(p.playerId);
        if (existing)
        {
            *existing = p;
        }
        else
        {
            if (chainTable[idx].search(p.playerId) != nullptr)
                numCollisions++; // já existia outro jogador ali
            chainTable[idx].insert(p);
            numElements++;
        }
    }
    else
    {
        int startIdx = idx;
        int probes = 0;
        while (openTable[idx].state == OCCUPIED)
        {
            if (openTable[idx].player.playerId == p.playerId)
            {
                openTable[idx].player = p;
                return;
            }
            idx = (idx + 1) % tableSize;
            probes++;
            if (idx == startIdx)
                return;
        }

        openTable[idx].player = p;
        openTable[idx].state = OCCUPIED;
        numElements++;

        if (probes > 0)
            numCollisions++;
    }
}

Player *Hash::searchById(long long id)
{
    int idx = hashFunction(id);
    if (method == CHAINING)
    {
        return chainTable[idx].search(id);
    }
    else
    {
        int startIdx = idx;
        while (openTable[idx].state != EMPTY)
        {
            if (openTable[idx].state == OCCUPIED && openTable[idx].player.playerId == id)
                return &openTable[idx].player;

            idx = (idx + 1) % tableSize;
            if (idx == startIdx)
                break;
        }
        return nullptr;
    }
}

bool Hash::remove(long long id)
{
    int idx = hashFunction(id);
    if (method == CHAINING)
    {
        if (chainTable[idx].remove(id))
        {
            numElements--;
            return true;
        }
    }
    else
    {
        int startIdx = idx;
        while (openTable[idx].state != EMPTY)
        {
            if (openTable[idx].state == OCCUPIED && openTable[idx].player.playerId == id)
            {
                openTable[idx].state = DELETED;
                numElements--;
                return true;
            }
            idx = (idx + 1) % tableSize;
            if (idx == startIdx)
                break;
        }
    }
    return false;
}

void Hash::printStats() const
{
    cout << "\n=== ESTATISTICAS ===" << endl;
    cout << "Tamanho da tabela: " << tableSize << endl;
    cout << "Elementos armazenados: " << numElements << endl;
    cout << "Fator de carga: " << (float)numElements / tableSize << endl;
    cout << "Numero de colisoes: " << numCollisions << endl;
}
