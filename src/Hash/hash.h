#ifndef HASH_H
#define HASH_H

#include "player.h"
#include "linked_list.h"
#include "hash_entry.h"
#include <vector>
#include <string>

using namespace std;

enum CollisionMethod
{
    CHAINING,
    LINEAR_PROBING
};

class Hash
{
private:
    int tableSize;
    int numElements;
    int numCollisions;
    CollisionMethod method;

    vector<LinkedList<Player>> chainTable;
    vector<HashEntry> openTable;

    int hashFunction(long long key) const;

public:
    Hash(int size = 10007, CollisionMethod method = CHAINING);

    void loadPlayers(const string &filePath);

    void insert(Player p);
    Player *searchById(long long id);
    bool remove(long long id);

    void printStats() const;
};

#endif
