#include "noB.h"
#include <vector>

using namespace std;

NoB::NoB(int ordemArvore, bool novoEFolha) {
    eFolha = novoEFolha;
    chavesPreenchidas = 0;
    chaves.resize(ordemArvore - 1);
    filhos.resize(ordemArvore);
}

void NoB::addChave(int novaChave){
    chaves[chavesPreenchidas++] = novaChave;
}

void NoB::addFilho(NoB* novoFilho){
    filhos.push_back(novoFilho);
}

void NoB::setEFolha(bool novoEFolha){
    eFolha = novoEFolha;
}
