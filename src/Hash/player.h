#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <iostream>

using namespace std;

struct Player {
    long long playerId;
    string country;
    string created;

    Player(long long id = -1, string c = "", string d = "")
        : playerId(id), country(c), created(d) {}

    friend ostream& operator<<(ostream& os, const Player& p) {
        os << "ID: " << p.playerId << ", Country: " << p.country << ", Created: " << p.created;
        return os;
    }
};

#endif