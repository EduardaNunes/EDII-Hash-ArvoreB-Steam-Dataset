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

string Player::getId()
{
    return id;
}

string Player::getPais()
{
    return pais;
}

string Player::getDataDeCriacao()
{
    return dataDeCriacao;
}

vector<Jogo> Player::getJogos()
{
    return jogos;
}

vector<Conquista> Player::getConquistas()
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
