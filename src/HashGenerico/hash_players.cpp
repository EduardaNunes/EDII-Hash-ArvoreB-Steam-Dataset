#include <cmath>

#include "./hash_players.h"

using namespace std;

LeitorDePlanilha leitor;
Utils utils;

void HashPlayers::populaTabelaComPlayers(TabelaHash<Player> &tabelaAlvo, MetodoDeColisao metodoDeColisao)
{
    cout << "Populando tabela com jogadores...\n";
    adicionaPlayersNaHash(tabelaAlvo);

    cout << "Adicionando jogos aos jogadores...\n";
    adicionaJogosNosPlayers(tabelaAlvo, metodoDeColisao);

    cout << "Adicionando conquistas aos jogadores...\n";
    adicionaConquistasNosPlayers(tabelaAlvo, metodoDeColisao);
}

void HashPlayers::adicionaPlayersNaHash(TabelaHash<Player> &tabelaJogadores)
{
    leitor.processarCSV(CSV_PLAYERS_PATH, [&](const vector<string> &linha)
                         {
        string id = linha[0];
        string pais = (linha.size() > 1) ? linha[1] : "";
        string dataCriacao = (linha.size() > 2) ? linha[2] : "";
        auto p = make_shared<Player>(id, pais, dataCriacao);
        tabelaJogadores.insere(p);
    });
}

void HashPlayers::adicionaJogosNaHash(TabelaHash<Jogo> &tabelaJogos)
{
    leitor.processarCSV(CSV_GAMES_PATH, [&](const vector<string> &linha)
                         {
        string id = (linha.size() > 0 && !linha[0].empty()) ? linha[0] : "";
        string titulo = (linha.size() > 1) ? linha[1] : "";
        vector<string> desenvolvedores = (linha.size() > 2) ? utils.split(linha[2], ',') : vector<string>{};
        vector<string> publishers = (linha.size() > 3) ? utils.split(linha[3], ',') : vector<string>{};
        vector<string> generos = (linha.size() > 4) ? utils.split(linha[4], ',') : vector<string>{};
        vector<string> idiomas = (linha.size() > 5) ? utils.split(linha[5], ',') : vector<string>{};
        string dataDeLancamento = (linha.size() > 6) ? linha[6] : "";
        auto novoJogo = make_shared<Jogo>(id, titulo, desenvolvedores, publishers, generos, idiomas, dataDeLancamento);
        tabelaJogos.insere(novoJogo);
    });
}

void HashPlayers::adicionaJogosNosPlayers(TabelaHash<Player> &tabelaJogadores, MetodoDeColisao metodoDeColisao)
{
    int totalJogos = leitor.contadorCSV(CSV_GAMES_TESTE_PATH);
    int tamanhoTabela = static_cast<int>(totalJogos);
    tamanhoTabela = static_cast<int>(ceil(tamanhoTabela / 0.7));
    TabelaHash<Jogo> tabelaJogos(tamanhoTabela, metodoDeColisao);
    adicionaJogosNaHash(tabelaJogos);
    leitor.processarCSV(CSV_PURCHASED_GAMES_PATH, [&](const vector<string> &linha)
                         {
        string idPlayer = (linha.size() > 0 && !linha[0].empty()) ? linha[0] : "";
        vector<string> idJogosComprados = (linha.size() > 1) ? utils.split(linha[1], ',') : vector<string>{};
        auto player = tabelaJogadores.busca(idPlayer);
        if (!player)
            continue;
        vector<shared_ptr<Jogo>> jogos = player->getJogos();
        for (auto idJogo : idJogosComprados)
        {
            idJogo = leitor.limparCampoCSV(idJogo);
            if (!idJogo.empty())
            {
                auto jogo = tabelaJogos.busca(idJogo);
                if (jogo)
                {
                    bool jaTem = false;
                    for (const auto &j : jogos)
                    {
                        if (j.getId() == jogo->getId())
                        {
                            jaTem = true;
                            break;
                        }
                    }
                    if (!jaTem)
                    {
                        jogos.push_back(jogo);
                    }
                }
            }
        }
        if (player)
            player->setJogos(jogos);
    });
}

void HashPlayers::adicionaConquistasNaHash(TabelaHash<Conquista> &tabelaConquistas)
{
    leitor.processarCSV(CSV_ACHIEVEMENTS_PATH, [&](const vector<string> &linha)
                         {
        string id = (linha.size() > 0 && !linha[0].empty()) ? linha[0] : "";
        string idJogo = (linha.size() > 1 && !linha[1].empty()) ? linha[1] : "";
        string titulo = (linha.size() > 2) ? linha[2] : "";
        string descricao = (linha.size() > 3) ? linha[3] : "";
        auto novaConquista = make_shared<Conquista>(id, idJogo, titulo, descricao);
        tabelaConquistas.insere(novaConquista);
    });
}

void HashPlayers::adicionaConquistasNosPlayers(TabelaHash<Player> &tabelaJogadores, MetodoDeColisao metodoDeColisao)
{
    int totalConquistas = leitor.contadorCSV(CSV_ACHIEVEMENTS_TESTE_PATH);
    int tamanhoTabela = static_cast<int>(totalConquistas);
    tamanhoTabela = static_cast<int>(ceil(tamanhoTabela / 0.7));
    TabelaHash<Conquista> tabelaConquistas(tamanhoTabela, metodoDeColisao);
    adicionaConquistasNaHash(tabelaConquistas);
    leitor.processarCSV(CSV_HISTORY_PATH, [&](const vector<string> &linha)
                         {
        string idPlayer = (linha.size() > 0 && !linha[0].empty()) ? linha[0] : "";
        string idConquista = (linha.size() > 1) ? linha[1] : "";
        auto conquista = tabelaConquistas.busca(idConquista);
        auto player = tabelaJogadores.busca(idPlayer);
        if (player && conquista)
            player->addConquista(conquista);
    });
}
