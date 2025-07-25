#include <vector>
#include <string>

#include "arvoreB.h"
#include "../HashGenerico/hash_generico.h"
#include "../Objetos/Player.h"

using namespace std;

// Construtor da ArvoreB
ArvoreB::ArvoreB(int novaOrdem){
    ordem = novaOrdem;
    raiz = new NoB(ordem, true); 
}

// Busca um jogador na árvore B pela chave
void ArvoreB::indexarPorJogos(const TabelaHash<Player>& tabelaJogadores) {
    tabelaJogadores.forEach([this](const shared_ptr<Player>& player) {
        if (player) {
            int qtdJogos = static_cast<int>(player->getJogos().size());
            insere(qtdJogos, player);
        }
    });
}

// Indexa jogadores na árvore B com base no número de conquistas
void ArvoreB::indexarPorConquistas(const TabelaHash<Player>& tabelaJogadores){
    tabelaJogadores.forEach([this](const shared_ptr<Player>& player) {
        if (player) {
            int qtdConquistas = static_cast<int>(player->getConquistas().size());
            insere(qtdConquistas, player);
        }
    });
}
// Busca um jogador na árvore B pela chave
vector<shared_ptr<Player>> ArvoreB::buscaTopJogadores(int quantidade){
    vector<shared_ptr<Player>> topJogadores;
    buscaTopJogadoresAuxiliar(raiz, quantidade, topJogadores);
    return topJogadores;
}

// Função auxiliar para buscar os top jogadores na árvore B
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

// Busca jogadores por intervalo de chaves na árvore B
vector<shared_ptr<Player>> ArvoreB::buscaPorIntervalo(int min, int max) {
    vector<shared_ptr<Player>> jogadores;
    buscaPorIntervaloAuxiliar(raiz, min, max, jogadores);
    return jogadores;
}

// Função auxiliar para buscar jogadores por intervalo de chaves na árvore B
void ArvoreB::buscaPorIntervaloAuxiliar(NoB* no, int min, int max, vector<shared_ptr<Player>>& jogadores) {
    if (!no) return;

    int i;
    for (i = 0; i < no->chavesPreenchidas; i++) {
        // Se não for folha, visita subárvore esquerda antes da chave
        if (!no->eFolha) {
            buscaPorIntervaloAuxiliar(no->filhos[i], min, max, jogadores);
        }

        int chave = no->chaves[i];
        if (chave >= min && chave <= max && no->jogadores[i]) {
            jogadores.push_back(no->jogadores[i]);
        }
    }

    // Último filho à direita
    if (!no->eFolha) {
        buscaPorIntervaloAuxiliar(no->filhos[i], min, max, jogadores);
    }
}

// Insere um novo jogador na árvore B
void ArvoreB::insere(int chave, shared_ptr<Player> jogador){

    if (raiz->chavesPreenchidas == (ordem - 1)) {

        NoB* novaRaiz = new NoB(ordem, false);
        novaRaiz->filhos[0] = raiz;

        dividirFilho(novaRaiz, 0, raiz);
        raiz = novaRaiz;
    }

    inserirNaoCheio(raiz, chave, jogador);

}

// Insere um jogador em um nó que não está cheio
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

// Divide um filho de um nó quando ele está cheio
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

// Busca um jogador na árvore B pela chave
shared_ptr<Player> ArvoreB::busca(int chave) {
    if (raiz->chavesPreenchidas == 0) {
        return nullptr;
    }
    return buscaAuxiliar(raiz, chave);
}

// Função auxiliar para buscar um jogador na árvore B
shared_ptr<Player> ArvoreB::buscaAuxiliar(NoB* no, int chave) {
    int i = 0;

    while (i < no->chavesPreenchidas && chave > no->chaves[i]) {
        i++;
    }

    if (i < no->chavesPreenchidas && chave == no->chaves[i]) {
        return no->jogadores[i]; // retorna o jogador encontrado
    }

    if (no->eFolha) {
        return nullptr; // não encontrou
    }

    return buscaAuxiliar(no->filhos[i], chave);
}

// Retorna a ordem da árvore B
int ArvoreB::getOrdem(){
    return ordem;
}

// Retorna a raiz da árvore B
NoB* ArvoreB::getRaiz(){
    return raiz;
}