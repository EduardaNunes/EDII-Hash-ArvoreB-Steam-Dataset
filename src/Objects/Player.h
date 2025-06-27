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
    long long id;
    string pais;
    string dataDeCriacao;
    vector<Jogo> jogos;
    vector<Conquista> conquistas;

public:
    Player(); 
    Player(long long id, string pais, string dataDeCriacao);

    long long getId();
    string getPais();
    string getDataDeCriacao();
    vector<Jogo> getJogos();
    vector<Conquista> getConquistas();

    void addConquista(Conquista novaConquista);
    void addJogo(Jogo novoJogo);

    friend ostream &operator<<(ostream &os, const Player &p)
    {
        os << "ID: " << p.id << ", Country: " << p.pais << ", Created: " << p.dataDeCriacao;
        return os;
    }
};

#endif