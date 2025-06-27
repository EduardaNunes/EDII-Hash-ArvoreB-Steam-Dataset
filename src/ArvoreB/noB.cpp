#include "noB.h"

NoB::NoB(int ordemArvore, bool novoEFolha) {
    eFolha = novoEFolha;
    chavesPreenchidas = 0;
    chaves.resize(ordemArvore - 1);
    filhos.resize(ordemArvore);
}
