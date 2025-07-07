#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include "Jogo.h"
#include "Conquista.h"
#include <iomanip>

using namespace std;
// A classe Player representa um jogador no sistema, contendo informações de ID, país, data de criação da conta, jogos associados e conquistas obtidas.
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
    Player(string id, string pais);

    string getId() const;
    string getPais() const;
    string getDataDeCriacao() const;
    vector<shared_ptr<Jogo>> getJogos() const;
    vector<shared_ptr<Conquista>> getConquistas() const;

    void addConquista(shared_ptr<Conquista> novaConquista);
    void setJogos(vector<shared_ptr<Jogo>> novosJogos);

    friend ostream &operator<<(ostream &os, const Player &p)
    {
        os << "\n==================================== PLAYER ====================================\n";
        os << left
        << setw(23) << "ID"
        << setw(15) << "Pais"
        << setw(20) << "Data de Criacao"
        << setw(10) << "Jogos"
        << "Conquistas" << endl;

        os << string(80, '-') << endl;

        os << left
        << setw(23) << p.id
        << setw(15) << p.pais
        << setw(20) << p.dataDeCriacao
        << setw(10) << p.jogos.size()
        << p.conquistas.size() << endl;

        os << string(80, '=') << "\n";

        return os;
    }
};

#endif