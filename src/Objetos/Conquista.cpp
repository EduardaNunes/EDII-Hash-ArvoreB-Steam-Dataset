#include <string>
#include "Conquista.h"

using namespace std;

Conquista::Conquista(string novoId, string novoIdJogo, string novoTitulo, string novaDescricao){
    id = novoId;
    idJogo = novoIdJogo;
    titulo = novoTitulo;
    descricao = novaDescricao;
}

string Conquista::getId(){
    return id;
}

string Conquista::getIdJogo(){
    return idJogo;
}

string Conquista::getTitulo(){
    return titulo;    
}

string Conquista::getDescricao(){
    return descricao;
}

