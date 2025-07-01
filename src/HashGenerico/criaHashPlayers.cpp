#include <cmath>

#include "../HashGenerico/hash_generico.h"
#include "../LeitorDePlanilha/leitorDePlanilha.h"
#include "../config.h"
#include "../Utils/utils.h"
#include "../Objetos/Player.h"
#include "../Objetos/Conquista.h"
#include "../Objetos/Jogo.h"

using namespace std;

LeitorDePlanilha leitor;
Utils utils;

void criaHashDePlayers()
{

    int totalJogadores = leitor.contadorCSV(CSV_PLAYERS_PATH);
    int tamanhoTabela = static_cast<int>(totalJogadores);
    tamanhoTabela = static_cast<int>(ceil(tamanhoTabela / 0.7));

    TabelaHash<Player> tabelaPlayers(tamanhoTabela, MetodoDeColisao::ENCADEAMENTO);

    adicionaPlayersNaHash(tabelaPlayers);
    adicionaJogosNosPlayers(tabelaPlayers);
    // adicionaConquistasNosPlayers(tabelaPlayers);
}

void adicionaPlayersNaHash(TabelaHash<Player> tabelaJogadores)
{

    vector<vector<string>> dadosPlayer = leitor.lerCSV(CSV_PLAYERS_TESTE_PATH);

    for (const auto &linha : dadosPlayer)
    {

        long long id = stoll(linha[0]);
        string pais = (linha.size() > 1) ? linha[1] : "";
        string dataCriacao = (linha.size() > 2) ? linha[2] : "";

        Player p(id, pais, dataCriacao);
        tabelaJogadores.insere(p);
    }
}

void adicionaJogosNaHash(TabelaHash<Jogo> tabelaJogos)
{

    vector<vector<string>> dadosJogos = leitor.lerCSV(CSV_GAMES_TESTE_PATH);

    for (const auto &linha : dadosJogos)
    {

        int id = (linha.size() > 0 && !linha[0].empty()) ? stoi(linha[0]) : 0;
        string titulo = (linha.size() > 1) ? linha[1] : "";
        vector<string> desenvolvedores = (linha.size() > 2) ? utils.split(linha[2], ',') : vector<string>{};
        vector<string> publishers = (linha.size() > 3) ? utils.split(linha[3], ',') : vector<string>{};
        vector<string> generos = (linha.size() > 4) ? utils.split(linha[4], ',') : vector<string>{};
        vector<string> idiomas = (linha.size() > 5) ? utils.split(linha[5], ',') : vector<string>{};
        string dataDeLancamento = (linha.size() > 6) ? linha[6] : "";

        Jogo novoJogo(id, titulo, desenvolvedores, publishers, generos, idiomas, dataDeLancamento);
        tabelaJogos.insere(novoJogo);
    }
}

void adicionaJogosNosPlayers(TabelaHash<Player> tabelaJogadores)
{

    int totalJogos = leitor.contadorCSV(CSV_GAMES_TESTE_PATH);
    int tamanhoTabela = static_cast<int>(totalJogos);
    tamanhoTabela = static_cast<int>(ceil(tamanhoTabela / 0.7));

    TabelaHash<Jogo> tabelaJogos(tamanhoTabela, MetodoDeColisao::ENCADEAMENTO);

    adicionaJogosNaHash(tabelaJogos);

    vector<vector<string>> dadosCompras = leitor.lerCSV(CSV_PURCHASED_GAMES_TESTE_PATH);

    for (const auto &linha : dadosCompras)
    {

        int idPlayer = (linha.size() > 0 && !linha[0].empty()) ? stoi(linha[0]) : 0;
        vector<string> idJogosComprados = (linha.size() > 1) ? utils.split(linha[1], ',') : vector<string>{};

        Player *player = tabelaJogadores.busca(idPlayer);
        vector<Jogo> jogos;

        for (const auto &idJogo : idJogosComprados)
        {

            if (!idJogo.empty())
            {

                int id = stoi(idJogo);
                Jogo *jogo = tabelaJogos.busca(id);

                if (jogo)
                {
                    jogos.push_back(*jogo);
                }
            }
        }

        player->setJogos(jogos);
    }
}

void adicionaConquistasNaHash(TabelaHash<Conquista> tabelaConquistas)
{

    vector<vector<string>> dadosConquistas = leitor.lerCSV(CSV_ACHIEVEMENTS_TESTE_PATH);

    for (const auto &linha : dadosConquistas){

        string id = (linha.size() > 0 && !linha[0].empty()) ? linha[0] : "";
        int idJogo = (linha.size() > 1  && !linha[0].empty()) ? stoi(linha[1]) : 0;
        string titulo = (linha.size() > 2) ? linha[2] : "";
        string descricao = (linha.size() > 3) ? linha[3] : "";

        Conquista novaConquista(id, idJogo, titulo, descricao);
        tabelaConquistas.insere(novaConquista);
    }
}

void adicionaConquistasNosPlayers(TabelaHash<Player> tabelaJogadores){
    int totalConquistas = leitor.contadorCSV(CSV_ACHIEVEMENTS_TESTE_PATH);
    int tamanhoTabela = static_cast<int>(totalConquistas);
    tamanhoTabela = static_cast<int>(ceil(tamanhoTabela / 0.7));

    TabelaHash<Conquista> tabelaConquistas(tamanhoTabela, MetodoDeColisao::ENCADEAMENTO);

    adicionaConquistasNaHash(tabelaConquistas);

    vector<vector<string>> dadosConquistas = leitor.lerCSV(CSV_HISTORY_TESTE_PATH);
    

    for (const auto& linha : dadosConquistas) {

        long long idPlayer =  (linha.size() < 2 || linha[0].empty()) ? stoll(linha[0]) : 0;
        string idConquista = (linha.size() > 1) ? linha[1] : "";

        Conquista *conquista = tabelaConquistas.busca(idConquista);
        Player *player = tabelaJogadores.busca(idPlayer);
        player->addConquista(*conquista);
    }

}