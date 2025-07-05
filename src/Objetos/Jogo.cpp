#include <string>
#include <vector>
#include "Jogo.h"

using namespace std;

Jogo::Jogo(string novoId, string novoTitulo, vector<string> novosDesenvolvedores, vector<string> novosPublishers, vector<string> novosGeneros, vector<string> novosIdiomas, string novaDataDeLancamento){
    id = novoId;
    titulo = novoTitulo;
    desenvolvedores = novosDesenvolvedores;
    publishers = novosPublishers;
    generos = novosGeneros;
    idiomas = novosIdiomas;
    dataDeLancamento = novaDataDeLancamento;
}

string Jogo::getId() const {
    return id;
};

string Jogo::getTitutlo(){
    return titulo;
};

vector<string> Jogo::getDesenvolvedores(){
    return desenvolvedores;
};

vector<string> Jogo::getPublishers(){
    return publishers;
};

vector<string> Jogo::getGeneros(){
    return generos;
};

vector<string> Jogo::getIdiomas(){
    return idiomas;
};

string Jogo::getDataDeLancamento(){
    return dataDeLancamento;
};

void Jogo::adicionaConquista(shared_ptr<Conquista> novaConquista){
    conquistas.push_back(novaConquista);
}