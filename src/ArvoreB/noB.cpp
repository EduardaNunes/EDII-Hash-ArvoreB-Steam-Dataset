#include "noB.h"
#include <vector>

using namespace std;

NoB::NoB(int ordemArvore, bool novoEFolha) {
    eFolha = novoEFolha;
    chavesPreenchidas = 0;
    chaves.resize(ordemArvore - 1);
    jogadores.resize(ordemArvore - 1);
    filhos.resize(ordemArvore);
}

void NoB::addChave(int novaChave, shared_ptr<Player> jogador) {
    int i = chavesPreenchidas - 1;

    // desloca os elementos para a direita dentro do vetor
    while (i >= 0 && novaChave < chaves[i]) {
        chaves[i + 1] = chaves[i];
        jogadores[i + 1] = jogadores[i];
        i--;
    }

    chaves[i + 1] = novaChave;
    jogadores[i + 1] = jogador;
    chavesPreenchidas++;
}


void NoB::addFilho(NoB* novoFilho){
    filhos.push_back(novoFilho);
}

void NoB::setEFolha(bool novoEFolha){
    eFolha = novoEFolha;
}
