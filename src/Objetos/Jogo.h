#ifndef JOGO_H
#define JOGO_H

#include <string>
#include <vector>
#include "Conquista.h"

using namespace std;

class Jogo{
    private:
        string id;
        string titulo;
        vector<string> desenvolvedores;
        vector<string> publishers;
        vector<string> generos;
        vector<string> idiomas;
        string dataDeLancamento;
        vector<Conquista> conquistas;

    public:
        Jogo(string id, string titulo, vector<string> desenvolvedores, vector<string> publishers, vector<string> generos, vector<string> idiomas, string dataDeLancamento);
        Jogo(){};

        string getId() const;
        string getTitutlo();
        vector<string> getDesenvolvedores();
        vector<string> getPublishers();
        vector<string> getGeneros();
        vector<string> getIdiomas();
        string getDataDeLancamento();
        Conquista getConquistas();

        void adicionaConquista(Conquista novaConquista);

    friend ostream& operator<<(ostream& os, const Jogo& jogo) {
        os << jogo.titulo;
        return os;
    }
};

#endif 