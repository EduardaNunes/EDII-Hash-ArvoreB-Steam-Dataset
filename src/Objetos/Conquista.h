#ifndef CONQUISTA_H
#define CONQUISTA_H

#include <string>
using namespace std;

class Conquista{
    private:
        string id;
        int idJogo;
        string titulo;
        string descricao;

    public:
        Conquista(string id, int idJogo, string titulo, string descricao);

        string getId();
        int getIdJogo();
        string getTitulo();
        string getDescricao();
};

#endif 