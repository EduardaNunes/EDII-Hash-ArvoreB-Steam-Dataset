#pragma once
#include <vector>
#include "ArvoreB.h"

using namespace std;

// Declara NoB como uma classe amiga de ArvoreB para permitir acesso aos seus membros privados
class NoB
{
private:
    vector<int> chaves;
    vector<NoB *> filhos;
    vector<std::shared_ptr<Player>> jogadores;
    int chavesPreenchidas;
    bool eFolha;

public:
    NoB(int ordemArvore, bool eFolha);

    void addChave(int novaChave, shared_ptr<Player> jogador);
    void addFilho(NoB *novoFilho);

    void setEFolha(bool novoEFolha);

    friend class ArvoreB;
};