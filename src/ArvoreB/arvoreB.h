#pragma once
#include <vector>
#include "../HashGenerico/hash_generico.h"
#include "../Objetos/Player.h"
#include "noB.h"

using namespace std;

class NoB;

class ArvoreB{
    private:
        int ordem;
        NoB* raiz;

        bool buscaAuxiliar(NoB* no, int chave);
        void inserirNaoCheio(NoB* no, int chave, shared_ptr<Player> jogador);
        void dividirFilho(NoB* pai, int i, NoB* y);

        void buscaTopJogadoresAuxiliar(NoB* no, int quantidade, vector<shared_ptr<Player>>& jogadores);

    public:

        ArvoreB(int ordem);

        bool busca(int chave);
        void insere(int chave,shared_ptr<Player> jogador);

        int getOrdem();
        NoB* getRaiz();

        void indexarPorJogos(const TabelaHash<Player>& tabelaJogadores);
        void indexarPorConquistas(const TabelaHash<Player>& tabelaJogadores);

        vector<shared_ptr<Player>> buscaTopJogadores(int quantidade);
};