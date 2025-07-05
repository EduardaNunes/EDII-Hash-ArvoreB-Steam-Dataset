#include <string>
#include <vector>
#include "Player.h"

using namespace std;

Player::Player()
{
    id = "";
    pais = "";
    dataDeCriacao = "";
}

Player::Player(string novoId, string novoPais, string novaDataDeCriacao)
{
    id = novoId;
    pais = novoPais;
    dataDeCriacao = novaDataDeCriacao;
}

string Player::getId() const
{
    return id;
}

string Player::getPais() const
{
    return pais;
}

string Player::getDataDeCriacao() const
{
    return dataDeCriacao;
}

vector<Jogo> Player::getJogos() const
{
    return jogos;
}

vector<Conquista> Player::getConquistas() const
{
    return conquistas;
}

void Player::addConquista(Conquista novaConquista)
{
    conquistas.push_back(novaConquista);
}

void Player::setJogos(vector<Jogo> novosJogos)
{
    jogos = novosJogos;
}
