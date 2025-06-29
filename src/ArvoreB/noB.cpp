#include "noB.h"
#include <vector>

using namespace std;

NoB::NoB(int ordemArvore, bool novoEFolha) {
    eFolha = novoEFolha;
    chavesPreenchidas = 0;
    chaves.resize(ordemArvore - 1);
    filhos.resize(ordemArvore);
}

// vector<int> NoB::getChaves(){
//     return chaves;
// }

// vector<NoB*> NoB::getFilhos(){
//     return filhos;
// }

// int NoB::getChavesPreenchidas(){
//     return chavesPreenchidas;
// }

// bool NoB::getEFolha(){
//     return eFolha;
// }

void NoB::addChave(int novaChave){
    chaves.push_back(novaChave);
    chavesPreenchidas++;
}

void NoB::addFilho(NoB* novoFilho){
    filhos.push_back(novoFilho);
}

void NoB::setEFolha(bool novoEFolha){
    eFolha = novoEFolha;
}
