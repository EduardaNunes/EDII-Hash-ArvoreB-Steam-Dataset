#pragma once
#include <vector>
#include "ArvoreB.h"

using namespace std;

class NoB {
    private:
        vector<int> chaves;
        vector <NoB*> filhos;
        int chavesPreenchidas;
        bool eFolha;
    
    public:
        NoB(int ordemArvore, bool eFolha);

        void addChave(int novaChave);
        void addFilho(NoB* novoFilho);

        void removeChave();
        void removeFilho();

        void setEFolha(bool novoEFolha);

    friend class ArvoreB;

};