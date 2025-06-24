#ifndef PLAYER_HASH_TABLE_H
#define PLAYER_HASH_TABLE_H

#include "player.h"
#include "linked_list.h"
#include "hash_entry.h"
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
    vector<HashEntry> probingTable;
    int computeHashIndex(long long key) const;

public:
    PlayerHashTable(int size = 10007, CollisionMethod method = CollisionMethod::CHAINING);

    void loadPlayersFromCSV(const string &filePath);

    void insertPlayer(Player p);
    Player *findPlayerById(long long id);
    bool removePlayerById(long long id);

    void exibirEstatisticas() const;
};

#endif
