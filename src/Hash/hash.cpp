#include <iostream>
#include <fstream>
#include <sstream>
#include "hash.h"
#include "../config.h"
#include "player.h"
#include <vector>

using namespace std;

vector<Player> Hash::readCSV(){
    vector<Player> players;
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
        players.emplace_back(id, country, created);
    }

    return players;
}

void Hash::showHash()
{
    vector<Player> list_Players = readCSV();

    cout << list_Players[1] << endl;
}