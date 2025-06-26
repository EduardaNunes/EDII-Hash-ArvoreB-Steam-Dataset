#include <string>
#include "Conquista.h"

using namespace std;

Conquista::Conquista(int novoId, Jogo novoJogo, string novoTitulo, string novaDescricao){
    id = novoId;
    jogo = novoJogo;
    titulo = novoTitulo;
    descricao = novaDescricao;
}

int Conquista::getId(){
    return id;
}

Jogo Conquista::getJogo(){
    return jogo;
}

string Conquista::getTitulo(){
    return titulo;    
}

string Conquista::getDescricao(){
    return descricao;
}

