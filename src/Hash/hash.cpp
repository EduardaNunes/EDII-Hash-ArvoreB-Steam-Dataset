#include <iostream>
#include <fstream>
#include "hash.h"
#include "../config.h"

using namespace std;

void Hash::showHash()
{
    ifstream players_data(CSV_PLAYERS_PATH);
    string teste;
    getline(players_data, teste);
    cout << teste << endl;
}