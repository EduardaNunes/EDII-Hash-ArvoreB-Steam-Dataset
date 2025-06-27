#include <string>
#include "Conquista.h"

using namespace std;

Conquista::Conquista(int novoId, int novoIdJogo, string novoTitulo, string novaDescricao){
    id = novoId;
    idJogo = novoIdJogo;
    titulo = novoTitulo;
    descricao = novaDescricao;
}

int Conquista::getId(){
    return id;
}

int Conquista::getIdJogo(){
    return idJogo;
}

string Conquista::getTitulo(){
    return titulo;    
}

string Conquista::getDescricao(){
    return descricao;
}

