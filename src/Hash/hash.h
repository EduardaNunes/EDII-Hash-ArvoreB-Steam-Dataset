#ifndef PLAYER_HASH_TABLE_H
#define PLAYER_HASH_TABLE_H

#include "../Objetos/Player.h"
#include "../HashGenerico/linked_list.h"
#include "../HashGenerico/hash_entry.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

enum class CollisionMethod
{
    CHAINING,
    LINEAR_PROBING
};

class PlayerHashTable
{
private:
    int tableSize;
    int elementCount;
    int collisionCount;
    CollisionMethod collisionMethod;

    vector<LinkedList<Player>> chainingTable;
    vector<HashEntry<Player>> probingTable;  // <-- Usar template HashEntry<Player>
    
    int computeHashIndex(long long key) const;
    void rehash();
    bool isPrime(int number);
    int nextPrime(int number);

public:
    PlayerHashTable(int size = 10007, CollisionMethod method = CollisionMethod::CHAINING);

    void loadPlayersFromCSV(const string &filePath);

    void insertPlayer(Player p);
    Player *findPlayerById(long long id);

    void exibirEstatisticas() const;
};

#endif
