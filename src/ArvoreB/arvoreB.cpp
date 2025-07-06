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
            insere(qtdJogos);
        }
    });
}

void ArvoreB::indexarPorConquistas(const TabelaHash<Player>& tabelaJogadores){
    tabelaJogadores.forEach([this](const shared_ptr<Player>& player) {
        if (player) {
            int qtdConquistas = static_cast<int>(player->getConquistas().size());
            insere(qtdConquistas);
        }
    });
}

void ArvoreB::insere(int chave){

    if (raiz->chavesPreenchidas == (ordem - 1)) {

        NoB* novaRaiz = new NoB(ordem, false);
        novaRaiz->filhos[0] = raiz;

        dividirFilho(novaRaiz, 0, raiz);
        raiz = novaRaiz;
    }

    inserirNaoCheio(raiz, chave);

}

void ArvoreB::inserirNaoCheio(NoB* no, int k) {
    int i = no->chavesPreenchidas - 1;

    if (no->eFolha) {
        while (i >= 0 && k < no->chaves[i]) {
            no->chaves[i + 1] = no->chaves[i];  // desloca pra direita
            i--;
        }
        no->chaves[i + 1] = k;                // insere no local certo
        no->chavesPreenchidas++;
    } else {
        while (i >= 0 && k < no->chaves[i]) i--;
        i++;

        if (no->filhos[i]->chavesPreenchidas == ordem - 1) {

            dividirFilho(no, i, no->filhos[i]);
            if (k > no->chaves[i]) i++;

        }

        inserirNaoCheio(no->filhos[i], k); // desce recursivamente
    }
}

void ArvoreB::dividirFilho(NoB* pai, int i, NoB* y) {
    NoB* z = new NoB(ordem, y->eFolha);             // novo nó z
    z->chavesPreenchidas = (ordem - 1) / 2;                // metade das chaves

    for (int j = 0; j < z->chavesPreenchidas; j++)
        z->chaves[j] = y->chaves[j + (ordem + 1) / 2];  // copia metade para z

    if (!y->eFolha)
        for (int j = 0; j < z->chavesPreenchidas + 1; j++)
            z->filhos[j] = y->filhos[j + (ordem + 1) / 2];

    y->chavesPreenchidas = (ordem - 1) / 2; // ajusta y (original)

    // insere z como novo filho do pai
    for (int j = pai->chavesPreenchidas; j >= i + 1; j--)
        pai->filhos[j + 1] = pai->filhos[j];
    pai->filhos[i + 1] = z;

    // promove chave do meio de y para o pai
    for (int j = pai->chavesPreenchidas - 1; j >= i; j--)
        pai->chaves[j + 1] = pai->chaves[j];
    pai->chaves[i] = y->chaves[(ordem - 1) / 2];

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