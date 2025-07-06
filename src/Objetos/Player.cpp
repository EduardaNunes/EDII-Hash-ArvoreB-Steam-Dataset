#include <string>
#include <vector>
#include <ctime>
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

Player::Player(string novoId, string novoPais)
{
    id = novoId;
    pais = novoPais;

    char buffer[20];
    time_t tempoBruto;
    time(&tempoBruto);
    struct tm *infoTempo = localtime(&tempoBruto);

    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", infoTempo);

    dataDeCriacao = string(buffer);
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

vector<shared_ptr<Jogo>> Player::getJogos() const
{
    return jogos;
}

vector<shared_ptr<Conquista>> Player::getConquistas() const
{
    return conquistas;
}

void Player::addConquista(shared_ptr<Conquista> novaConquista)
{
    conquistas.push_back(novaConquista);
}

void Player::setJogos(vector<shared_ptr<Jogo>> novosJogos)
{
    jogos = novosJogos;
}
