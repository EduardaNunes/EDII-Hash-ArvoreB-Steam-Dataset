#pragma once
#include <vector>
#include "../HashGenerico/hash.h"
#include "../Objetos/Player.h"

using namespace std;

class NoB;

class ArvoreB{
    private:
        int ordem;
        NoB* raiz;

        bool buscaAuxiliar(NoB* no, int chave);
        void inserirNaoCheio(NoB* no, int chave);
        void dividirFilho(NoB* pai, int i, NoB* y);

    public:

        ArvoreB(int ordem);

        bool busca(int chave);
        void insere(int chave);
        void remove();

        int getOrdem();
        NoB* getRaiz();

        void indexarJogos();
        void indexarConquistas();
};