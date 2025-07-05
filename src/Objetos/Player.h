#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include "Jogo.h"
#include "Conquista.h"

using namespace std;

class Player
{
private:
    string id;
    string pais;
    string dataDeCriacao;
    vector<shared_ptr<Jogo>> jogos;
    vector<shared_ptr<Conquista>> conquistas;

public:
    Player();
    Player(string id, string pais, string dataDeCriacao);

    string getId() const;
    string getPais() const;
    string getDataDeCriacao() const;
    vector<shared_ptr<Jogo>> getJogos() const;
    vector<shared_ptr<Conquista>> getConquistas() const;

    void addConquista(shared_ptr<Conquista> novaConquista);
    void setJogos(vector<shared_ptr<Jogo>> novosJogos);

    friend ostream &operator<<(ostream &os, const Player &p)
    {
        os << "==================== PLAYER ====================\n"
        << "> ID: " << p.id << "\n"
        << "> País: " << p.pais << "\n"
        << "> Conta criada em: " << p.dataDeCriacao << "\n"
        << "> Quantidade de Jogos: " << p.jogos.size() << "\n"
        << "> Quantidade de Conquistas: " << p.conquistas.size() << "\n"
        << "================================================";
        return os;
    }
};

#endif