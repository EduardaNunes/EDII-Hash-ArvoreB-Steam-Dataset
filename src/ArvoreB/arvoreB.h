#include "NoB.h"

using namespace std;

class ArvoreB{
    private:
        int ordem;
        NoB* raiz;

    public:
        bool busca(int chave);
        void insere();
        void remove();

        int getOrdem();
        NoB* getRaiz();

        void indexarJogos();
        void indexarConquistas();
};