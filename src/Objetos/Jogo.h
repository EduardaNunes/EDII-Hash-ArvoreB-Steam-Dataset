#ifndef JOGO_H
#define JOGO_H

#include <string>
#include <vector>
#include <memory>
#include "Conquista.h"

using namespace std;
// A classe Jogo representa um jogo no sistema, contendo informações de ID, título, desenvolvedores, publishers, gêneros, idiomas, data de lançamento e conquistas associadas.
class Jogo
{
private:
    string id;
    string titulo;
    vector<string> desenvolvedores;
    vector<string> publishers;
    vector<string> generos;
    vector<string> idiomas;
    string dataDeLancamento;
    vector<shared_ptr<Conquista>> conquistas;

public:
    Jogo(string id, string titulo, vector<string> desenvolvedores, vector<string> publishers, vector<string> generos, vector<string> idiomas, string dataDeLancamento);
    Jogo() {};

    string getId() const;
    string getTitulo() const;
    vector<string> getDesenvolvedores();
    vector<string> getPublishers();
    vector<string> getGeneros();
    vector<string> getIdiomas();
    string getDataDeLancamento();
    vector<shared_ptr<Conquista>> getConquistas() const;

    void adicionaConquista(shared_ptr<Conquista> novaConquista);

    friend ostream &operator<<(ostream &os, const Jogo &jogo)
    {
        os << jogo.titulo;
        return os;
    }
};

#endif