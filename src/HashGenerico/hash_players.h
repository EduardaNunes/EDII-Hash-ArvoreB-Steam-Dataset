#include "../LeitorDePlanilha/leitorDePlanilha.h"
#include "../Objetos/Conquista.h"
#include "../Objetos/Player.h"
#include "../Objetos/Jogo.h"
#include "../Utils/utils.h"
#include "./hash_generico.h"
#include "../config.h"

using namespace std;

class HashPlayers
{
    private:
        void adicionaPlayersNaHash(TabelaHash<Player> &tabelaJogadores);
        void adicionaJogosNaHash(TabelaHash<Jogo> &tabelaJogos);
        void adicionaJogosNosPlayers(TabelaHash<Player> &tabelaJogadores, MetodoDeColisao metodoDeColisao);
        void adicionaConquistasNaHash(TabelaHash<Conquista> &tabelaConquistas);
        void adicionaConquistasNosPlayers(TabelaHash<Player> &tabelaJogadores, MetodoDeColisao metodoDeColisao);

    public:
        HashPlayers(){}
        void populaTabelaComPlayers(TabelaHash<Player>& tabelaAlvo, MetodoDeColisao metodoDeColisao); 
};
