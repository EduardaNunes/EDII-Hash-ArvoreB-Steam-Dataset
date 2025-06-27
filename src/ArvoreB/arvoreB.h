#include "NoB.h"

using namespace std;

class ArvoreB{
    private:
        int ordem;
        NoB* raiz;

    public:
        void busca();
        void insere();
        void remove();

        int getOrdem();
        NoB* getRaiz();

        void indexarJogos();
        void indexarConquistas();
};