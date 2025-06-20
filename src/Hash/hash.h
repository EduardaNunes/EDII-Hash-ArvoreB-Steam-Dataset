#ifndef HASH_H
#define HASH_H

#include "player.h"
#include <unordered_map>
#include <vector>

using namespace std;

class Hash {
private:
    unordered_map<long long, Player> table;

public:
    void loadPlayers();
    Player* searchById(long long id);
};

#endif
