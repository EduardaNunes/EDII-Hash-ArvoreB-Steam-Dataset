#pragma once
#include <vector>
#include "ArvoreB.h"

using namespace std;

class NoB {
    private:
        vector<int> chaves;
        vector <NoB*> filhos;
        vector<std::shared_ptr<Player>> jogadores;
        int chavesPreenchidas;
        bool eFolha;
    
    public:
        NoB(int ordemArvore, bool eFolha);

        void addChave(int novaChave, shared_ptr<Player> jogador);
        void addFilho(NoB* novoFilho);

        void setEFolha(bool novoEFolha);

    friend class ArvoreB;

};