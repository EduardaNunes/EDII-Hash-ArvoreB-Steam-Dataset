#pragma once
#include "noB.h"

using namespace std;

class ArvoreB{
    private:
        int ordem;
        NoB* raiz;

        bool buscaAuxiliar(NoB* no, int chave);

    public:

        ArvoreB(int ordem);

        bool busca(int chave);
        void insere(int chave);
        void remove();

        int getOrdem();
        NoB* getRaiz();

        void indexarJogos();
        void indexarConquistas();;
};