#include <vector>
#include <string>

#include "arvoreB.h"
#include "../HashGenerico/hash_generico.h"
#include "../Objetos/Player.h"

using namespace std;

ArvoreB::ArvoreB(int novaOrdem){
    ordem = novaOrdem;
    raiz = new NoB(ordem, true); 
}

void ArvoreB::indexarPorJogos(const TabelaHash<Player>& tabelaJogadores) {
    tabelaJogadores.forEach([this](const shared_ptr<Player>& player) {
        if (player) {
            int qtdJogos = static_cast<int>(player->getJogos().size());
            insere(qtdJogos, player);
        }
    });
}

void ArvoreB::indexarPorConquistas(const TabelaHash<Player>& tabelaJogadores){
    tabelaJogadores.forEach([this](const shared_ptr<Player>& player) {
        if (player) {
            int qtdConquistas = static_cast<int>(player->getConquistas().size());
            insere(qtdConquistas, player);
        }
    });
}

vector<shared_ptr<Player>> ArvoreB::buscaTopJogadores(int quantidade){
    vector<shared_ptr<Player>> topJogadores;
    buscaTopJogadoresAuxiliar(raiz, quantidade, topJogadores);
    return topJogadores;
}

void ArvoreB::buscaTopJogadoresAuxiliar(NoB* no, int quantidade, vector<shared_ptr<Player>>& jogadores) {
    if (!no || jogadores.size() >= quantidade) return;

    for (int i = no->chavesPreenchidas - 1; i >= 0; i--) {
        // Primeiro os filhos da direita (para ordem decrescente)
        if (!no->eFolha && jogadores.size() < quantidade) {
            buscaTopJogadoresAuxiliar(no->filhos[i + 1], quantidade, jogadores);
        }

        if (jogadores.size() >= quantidade) return;

        if (no->jogadores[i]) {
            jogadores.push_back(no->jogadores[i]);
        }

        if (jogadores.size() >= quantidade) return;
    }

    // Visita o último filho da esquerda
    if (!no->eFolha && jogadores.size() < quantidade) {
        buscaTopJogadoresAuxiliar(no->filhos[0], quantidade, jogadores);
    }
}


void ArvoreB::insere(int chave, shared_ptr<Player> jogador){

    if (raiz->chavesPreenchidas == (ordem - 1)) {

        NoB* novaRaiz = new NoB(ordem, false);
        novaRaiz->filhos[0] = raiz;

        dividirFilho(novaRaiz, 0, raiz);
        raiz = novaRaiz;
    }

    inserirNaoCheio(raiz, chave, jogador);

}

void ArvoreB::inserirNaoCheio(NoB* no, int chave, shared_ptr<Player> jogador) {
    int i = no->chavesPreenchidas - 1;

    if (no->eFolha) {
        no->addChave(chave, jogador);

    } else {
        while (i >= 0 && chave < no->chaves[i]) i--;
        i++;

        if (no->filhos[i]->chavesPreenchidas == ordem - 1) {

            dividirFilho(no, i, no->filhos[i]);
            if (chave > no->chaves[i]) i++;

        }

        inserirNaoCheio(no->filhos[i], chave, jogador); // desce recursivamente
    }
}

void ArvoreB::dividirFilho(NoB* pai, int i, NoB* filho) {
    NoB* novoFilho = new NoB(ordem, filho->eFolha);            
    novoFilho->chavesPreenchidas = (ordem - 1) / 2;            // metade das chaves

    for (int j = 0; j < novoFilho->chavesPreenchidas; j++)
        novoFilho->chaves[j] = filho->chaves[j + (ordem + 1) / 2];  // copia metade para novoFilho

    if (!filho->eFolha)
        for (int j = 0; j < novoFilho->chavesPreenchidas + 1; j++)
            novoFilho->filhos[j] = filho->filhos[j + (ordem + 1) / 2];

    filho->chavesPreenchidas = (ordem - 1) / 2; // ajusta filho (original)

    // insere novoFilho como novo filho do pai
    for (int j = pai->chavesPreenchidas; j >= i + 1; j--)
        pai->filhos[j + 1] = pai->filhos[j];
    pai->filhos[i + 1] = novoFilho;

    // promove chave do meio de filho para o pai
    for (int j = pai->chavesPreenchidas - 1; j >= i; j--)
        pai->chaves[j + 1] = pai->chaves[j];
    pai->chaves[i] = filho->chaves[(ordem - 1) / 2];

    pai->chavesPreenchidas++;
}

// Mudar depois de bool para o tipo de informação que será retornada
bool ArvoreB::busca(int chave){

    if(raiz->chavesPreenchidas == 0){
        return false;
    }

    return buscaAuxiliar(raiz, chave);
}

bool ArvoreB::buscaAuxiliar(NoB* no, int chave){

    int i = 0;
    
    while (i < no->chavesPreenchidas && chave > no->chaves[i]) {
        i++;
    }

    if (i < no->chavesPreenchidas && chave == no->chaves[i]) return true;

    if(no->eFolha) return false;
    return buscaAuxiliar(no->filhos[i], chave);
}

int ArvoreB::getOrdem(){
    return ordem;
}

NoB* ArvoreB::getRaiz(){
    return raiz;
}