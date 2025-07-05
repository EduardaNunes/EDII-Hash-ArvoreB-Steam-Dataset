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

    char buffer[11];
    time_t tempoBruto;
    time(&tempoBruto);
    struct tm *infoTempo = localtime(&tempoBruto);

    strftime(buffer, sizeof(buffer), "%Y-%m-%d", infoTempo);
    
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
