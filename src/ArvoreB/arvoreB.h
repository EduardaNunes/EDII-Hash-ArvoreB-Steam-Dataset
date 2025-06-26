#include "NoB.h"

using namespace std;

class ArvoreB{
    private:
        int ordem;
        NoB* raiz;

    public:
        void insere();
        void busca();
        void remove();

        int getOrdem();
        NoB* getRaiz();

        void indexarJogos();
        void indexarConquistas();
};