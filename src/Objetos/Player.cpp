#include <string>
#include <vector>
#include "Player.h"

using namespace std;

Player::Player(){
    id = 0;
    pais = "";
    dataDeCriacao = "";
}

Player::Player(int novoId, string novoPais, string novaDataDeCriacao){
    id = novoId;
    pais = novoPais;
    dataDeCriacao = novaDataDeCriacao;
}


int Player::getId(){
    return id;
};

string Player::getPais(){
    return pais;
};

string Player::getDataDeCriacao(){
    return dataDeCriacao;
};

vector<Jogo> Player::getJogos(){
    return jogos;
};

vector<Conquista> Player::getConquistas(){
    return conquistas;
};

void Player::addConquista(Conquista novaConquista){

};

void Player::setJogos(vector<Jogo> novosJogos){
    jogos = novosJogos;
};
