#include "noB.h"
#include <vector>

using namespace std;

// Construtor da classe NoB, que inicializa o nó com a ordem da árvore e se é folha ou não
NoB::NoB(int ordemArvore, bool novoEFolha)
{
    eFolha = novoEFolha;
    chavesPreenchidas = 0;
    chaves.resize(ordemArvore - 1);
    jogadores.resize(ordemArvore - 1);
    filhos.resize(ordemArvore);
}

// Método para adicionar uma nova chave e o jogador associado ao nó
void NoB::addChave(int novaChave, shared_ptr<Player> jogador)
{
    int i = chavesPreenchidas - 1;

    // desloca os elementos para a direita dentro do vetor
    while (i >= 0 && novaChave < chaves[i])
    {
        chaves[i + 1] = chaves[i];
        jogadores[i + 1] = jogadores[i];
        i--;
    }

    chaves[i + 1] = novaChave;
    jogadores[i + 1] = jogador;
    chavesPreenchidas++;
}

// Método para adicionar um novo filho ao nó
void NoB::addFilho(NoB *novoFilho)
{
    filhos.push_back(novoFilho);
}

// Método para definir se o nó é uma folha ou não
void NoB::setEFolha(bool novoEFolha)
{
    eFolha = novoEFolha;
}
