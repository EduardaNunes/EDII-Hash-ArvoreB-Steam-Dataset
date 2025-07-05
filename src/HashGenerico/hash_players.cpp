#include <cmath>

#include "./hash_players.h"

using namespace std;

LeitorDePlanilha leitor;
Utils utils;

TabelaHash<Player> HashPlayers::criaHashDePlayers(MetodoDeColisao metodoDeColisao)
{
    int totalJogadores = leitor.contadorCSV(CSV_PLAYERS_PATH);
    //int tamanhoTabela = static_cast<int>(totalJogadores);
    int tamanhoTabela = static_cast<int>(ceil(tamanhoTabela / 0.7));

    TabelaHash<Player> tabelaPlayers(tamanhoTabela, metodoDeColisao);

    adicionaPlayersNaHash(tabelaPlayers);
    adicionaJogosNosPlayers(tabelaPlayers, metodoDeColisao);
    adicionaConquistasNosPlayers(tabelaPlayers, metodoDeColisao);

    return tabelaPlayers;
}

void HashPlayers::adicionaPlayersNaHash(TabelaHash<Player> &tabelaJogadores)
{
    vector<vector<string>> dadosPlayer = leitor.lerCSV(CSV_PLAYERS_PATH);

    for (const auto &linha : dadosPlayer)
    {
        string id = linha[0];
        string pais = (linha.size() > 1) ? linha[1] : "";
        string dataCriacao = (linha.size() > 2) ? linha[2] : "";

        Player p(id, pais, dataCriacao);
        tabelaJogadores.insere(p);
    }
}

void HashPlayers::adicionaJogosNaHash(TabelaHash<Jogo> &tabelaJogos)
{
    vector<vector<string>> dadosJogos = leitor.lerCSV(CSV_GAMES_PATH);

    for (const auto &linha : dadosJogos)
    {
        string id = (linha.size() > 0 && !linha[0].empty()) ? linha[0] : "";
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

void HashPlayers::adicionaJogosNosPlayers(TabelaHash<Player> &tabelaJogadores, MetodoDeColisao metodoDeColisao)
{
    int totalJogos = leitor.contadorCSV(CSV_GAMES_TESTE_PATH);
    int tamanhoTabela = static_cast<int>(totalJogos);
    tamanhoTabela = static_cast<int>(ceil(tamanhoTabela / 0.7));

    TabelaHash<Jogo> tabelaJogos(tamanhoTabela, metodoDeColisao);

    adicionaJogosNaHash(tabelaJogos);

    vector<vector<string>> dadosCompras = leitor.lerCSV(CSV_PURCHASED_GAMES_PATH);

    for (const auto &linha : dadosCompras)
    {
        string idPlayer = (linha.size() > 0 && !linha[0].empty()) ? linha[0] : "";
        vector<string> idJogosComprados = (linha.size() > 1) ? utils.split(linha[1], ',') : vector<string>{};

        Player *player = tabelaJogadores.busca(idPlayer);
        vector<Jogo> jogos;

        for (const auto &idJogo : idJogosComprados)
        {
            if (!idJogo.empty())
            {
                Jogo *jogo = tabelaJogos.busca(idJogo);

                if (jogo)
                {
                    jogos.push_back(*jogo);
                }
            }
        }

        if (player)
            player->setJogos(jogos);
    }
}

void HashPlayers::adicionaConquistasNaHash(TabelaHash<Conquista> &tabelaConquistas)
{
    vector<vector<string>> dadosConquistas = leitor.lerCSV(CSV_ACHIEVEMENTS_PATH);

    for (const auto &linha : dadosConquistas)
    {
        string id = (linha.size() > 0 && !linha[0].empty()) ? linha[0] : "";
        string idJogo = (linha.size() > 1 && !linha[1].empty()) ? linha[1] : "";
        string titulo = (linha.size() > 2) ? linha[2] : "";
        string descricao = (linha.size() > 3) ? linha[3] : "";

        Conquista novaConquista(id, idJogo, titulo, descricao);
        tabelaConquistas.insere(novaConquista);
    }
}

void HashPlayers::adicionaConquistasNosPlayers(TabelaHash<Player> &tabelaJogadores, MetodoDeColisao metodoDeColisao)
{
    int totalConquistas = leitor.contadorCSV(CSV_ACHIEVEMENTS_PATH);
    int tamanhoTabela = static_cast<int>(totalConquistas);
    tamanhoTabela = static_cast<int>(ceil(tamanhoTabela / 0.7));

    TabelaHash<Conquista> tabelaConquistas(tamanhoTabela, metodoDeColisao);

    adicionaConquistasNaHash(tabelaConquistas);

    vector<vector<string>> dadosConquistas = leitor.lerCSV(CSV_HISTORY_PATH);

    for (const auto &linha : dadosConquistas)
    {
        string idPlayer = (linha.size() > 0 && !linha[0].empty()) ? linha[0] : "";
        string idConquista = (linha.size() > 1) ? linha[1] : "";

        Conquista *conquista = tabelaConquistas.busca(idConquista);
        Player *player = tabelaJogadores.busca(idPlayer);

        if (player && conquista)
            player->addConquista(*conquista);
    }
}
