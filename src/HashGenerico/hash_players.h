#include "../LeitorDePlanilha/leitorDePlanilha.h"
#include "../Objetos/Conquista.h"
#include "../Objetos/Player.h"
#include "../Objetos/Jogo.h"
#include "../Utils/utils.h"
#include "./hash_generico.h"
#include "../config.h"

using namespace std;

// struct JogadoresDoJogo guarda o ID do jogo e uma lista de jogadores que possuem esse jogo.
struct JogadoresDoJogo {
    string idJogo;
    vector<string> jogadores;

    string getId() const { return idJogo; }
    void addJogador(const string &id) {
        jogadores.push_back(id);
    }
    void imprimeJogadores() const {
        cout << "Jogadores do jogo " << idJogo << ":\n";
        for (const auto &jogadorId : jogadores) {
            cout << "Id do jogador: " << jogadorId << endl;
        }
    }
};

// HashPlayers é uma classe responsável por popular uma tabela hash com jogadores, jogos e conquistas.
class HashPlayers
{
private:
    void adicionaPlayersNaHash(TabelaHash<Player> &tabelaJogadores);
    void adicionaJogosNaHash(TabelaHash<Jogo> &tabelaJogos);
    void adicionaJogosNosPlayers(TabelaHash<Player> &tabelaJogadores, MetodoDeColisao metodoDeColisao);
    void adicionaConquistasNaHash(TabelaHash<Conquista> &tabelaConquistas);
    void adicionaConquistasNosPlayers(TabelaHash<Player> &tabelaJogadores, MetodoDeColisao metodoDeColisao);

public:
    HashPlayers() {}
    void populaTabelaComPlayers(TabelaHash<Player> &tabelaAlvo, MetodoDeColisao metodoDeColisao);
    void criaHashJogosParaJogadores(TabelaHash<JogadoresDoJogo> &tabelaJogosParaJogadores, const TabelaHash<Player> &tabelaPlayers);
};
