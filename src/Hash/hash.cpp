#include <iostream>
#include <fstream>
#include <sstream>
#include "hash.h"
#include "../config.h"

using namespace std;

void Hash::loadPlayers() {
    ifstream file(CSV_PLAYERS_PATH);
    string line;

    getline(file, line);

    while (getline(file, line)) {
        stringstream ss(line);
        string idStr, country, created;

        getline(ss, idStr, ',');
        getline(ss, country, ',');
        getline(ss, created, ',');

        long long id = stoll(idStr);
        table[id] = Player(id, country, created);
    }
}

Player* Hash::searchById(long long id) {
    auto it = table.find(id);
    if (it != table.end()) {
        return &(it->second);
    }
    return nullptr;
}
