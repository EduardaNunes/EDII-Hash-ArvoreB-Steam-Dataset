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
    Player(string id, string pais);

    string getId() const;
    string getPais() const;
    string getDataDeCriacao() const;
    vector<Jogo> getJogos() const;
    vector<Conquista> getConquistas() const;

    void addConquista(Conquista novaConquista);
    void setJogos(vector<Jogo> novosJogos);

    friend ostream &operator<<(ostream &os, const Player &p)
    {
        os << "==================== PLAYER ====================\n"
        << "> ID: " << p.id << "\n"
        << "> Pais: " << p.pais << "\n"
        << "> Conta criada em: " << p.dataDeCriacao << "\n"
        << "> Quantidade de Jogos: " << p.jogos.size() << "\n"
        << "> Quantidade de Conquistas: " << p.conquistas.size() << "\n"
        << "================================================";
        return os;
    }
};

#endif