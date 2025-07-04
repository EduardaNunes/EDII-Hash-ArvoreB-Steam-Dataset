#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include <iostream>
#include "Jogo.h"
#include "Conquista.h"

using namespace std;

class Player
{
private:
    string id;
    string pais;
    string dataDeCriacao;
    vector<Jogo> jogos;
    vector<Conquista> conquistas;

public:
    Player();
    Player(string id, string pais, string dataDeCriacao);

    string getId();
    string getPais();
    string getDataDeCriacao();
    vector<Jogo> getJogos();
    vector<Conquista> getConquistas();

    void addConquista(Conquista novaConquista);
    void setJogos(vector<Jogo> novosJogos);

    friend ostream &operator<<(ostream &os, const Player &p)
    {
        os << "ID: " << p.id << ", Country: " << p.pais << ", Created: " << p.dataDeCriacao;
        return os;
    }
};

#endif