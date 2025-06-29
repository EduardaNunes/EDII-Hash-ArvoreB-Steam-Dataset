#ifndef JOGO_H
#define JOGO_H

#include <string>
#include <vector>
#include "Conquista.h"

using namespace std;

class Jogo{
    private:
        int id;
        string titulo;
        vector<string> desenvolvedores;
        vector<string> publishers;
        vector<string> generos;
        vector<string> idiomas;
        string dataDeLancamento;
        vector<Conquista> conquistas;

    public:
        Jogo(int id, string titulo, vector<string> desenvolvedores, vector<string> publishers, vector<string> generos, vector<string> idiomas, string dataDeLancamento);

        int getId();
        string getTitutlo();
        vector<string> getDesenvolvedores();
        vector<string> getPublishers();
        vector<string> getGeneros();
        vector<string> getIdiomas();
        string getDataDeLancamento();
        Conquista getConquistas();

        void adicionaConquista(Conquista novaConquista);
};

#endif 