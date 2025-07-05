#ifndef CONQUISTA_H
#define CONQUISTA_H

#include <string>
using namespace std;

class Conquista{
    private:
        string id;
        string idJogo;
        string titulo;
        string descricao;

    public:
        Conquista(string id, string idJogo, string titulo, string descricao);

        string getId();
        string getIdJogo();
        string getTitulo();
        string getDescricao();

    friend ostream& operator<<(ostream& os, const Conquista& c) {
        os << c.titulo;
        return os;
    }
};

#endif 