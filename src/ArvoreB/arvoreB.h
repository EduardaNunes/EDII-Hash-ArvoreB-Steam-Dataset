#pragma once
#include <vector>
#include "../HashGenerico/hash_generico.h"
#include "../Objetos/Player.h"
#include "noB.h"

using namespace std;

// Enum para definir os tipos de indexação da árvore B
enum class TipoDeIndexacao
{
    JOGOS,
    CONQUISTAS
};

// Declaração antecipada da classe NoB para evitar dependências circulares
class NoB;

// Classe ArvoreB representa uma árvore B genérica, que pode ser usada para indexar jogadores por jogos ou conquistas.
class ArvoreB
{
private:
    int ordem;
    NoB *raiz;

    shared_ptr<Player> buscaAuxiliar(NoB *no, int chave);
    void inserirNaoCheio(NoB *no, int chave, shared_ptr<Player> jogador);
    void dividirFilho(NoB *pai, int i, NoB *y);

    void buscaTopJogadoresAuxiliar(NoB *no, int quantidade, vector<shared_ptr<Player>> &jogadores);
    void buscaPorIntervaloAuxiliar(NoB* no, int min, int max, vector<shared_ptr<Player>>& jogadores);

public:
    ArvoreB(int ordem);

    shared_ptr<Player> busca(int chave);
    void insere(int chave, shared_ptr<Player> jogador);

    int getOrdem();
    NoB *getRaiz();

    void indexarPorJogos(const TabelaHash<Player> &tabelaJogadores);
    void indexarPorConquistas(const TabelaHash<Player> &tabelaJogadores);

    vector<shared_ptr<Player>> buscaTopJogadores(int quantidade);
    vector<shared_ptr<Player>> buscaPorIntervalo(int min, int max);

};