#pragma once
#include "noB.h"

using namespace std;

class ArvoreB{
    private:
        int ordem;
        NoB* raiz;

        bool buscaAuxiliar(NoB* no, int chave);

    public:
        bool busca(int chave);
        void insere();
        void remove();

        int getOrdem();
        NoB* getRaiz();

        void indexarJogos();
        void indexarConquistas();
};