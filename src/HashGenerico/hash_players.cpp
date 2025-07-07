#include <cmath>
#include <unordered_set>

#include "./hash_players.h"

using namespace std;

LeitorDePlanilha leitor;
Utils utils;

// Função que popula a tabela hash com jogadores, jogos e conquistas
void HashPlayers::populaTabelaComPlayers(TabelaHash<Player> &tabelaAlvo, MetodoDeColisao metodoDeColisao)
{
    cout << "Populando tabela com jogadores...\n";
    adicionaPlayersNaHash(tabelaAlvo);

    cout << "Adicionando jogos aos jogadores...\n";
    adicionaJogosNosPlayers(tabelaAlvo, metodoDeColisao);

    cout << "Adicionando conquistas aos jogadores...\n";
    adicionaConquistasNosPlayers(tabelaAlvo, metodoDeColisao);
}

// Adiciona jogadores na tabela hash a partir de um arquivo CSV
void HashPlayers::adicionaPlayersNaHash(TabelaHash<Player> &tabelaJogadores)
{
    leitor.processarCSV(CSV_PLAYERS_PATH, [&](const vector<string> &linha)
                        {

        string id = linha[0];
        string pais = (linha.size() > 1) ? linha[1] : "";
        string dataCriacao = (linha.size() > 2) ? linha[2] : "";

        auto novoJogador = make_shared<Player>(id, pais, dataCriacao);
        tabelaJogadores.insere(novoJogador); });
}

// Adiciona jogos na tabela hash a partir de um arquivo CSV
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
        tabelaJogos.insere(novoJogo); });
}

// Adiciona jogos aos jogadores a partir de um arquivo CSV
void HashPlayers::adicionaJogosNosPlayers(TabelaHash<Player> &tabelaJogadores, MetodoDeColisao metodoDeColisao)
{
    int totalJogos = leitor.contadorCSV(CSV_GAMES_PATH);
    int tamanhoTabela = static_cast<int>(totalJogos);
    tamanhoTabela = static_cast<int>(ceil(tamanhoTabela / 0.7));

    TabelaHash<Jogo> tabelaJogos(tamanhoTabela, metodoDeColisao);
    adicionaJogosNaHash(tabelaJogos);

    leitor.processarCSV(CSV_PURCHASED_GAMES_PATH, [&](const vector<string> &linha)
                        {

        string idPlayer = (linha.size() > 0 && !linha[0].empty()) ? linha[0] : "";
        vector<string> idJogosComprados = (linha.size() > 1) ? utils.split(linha[1], ',') : vector<string>{};
        auto player = tabelaJogadores.busca(idPlayer);

        if (!player) return;

        vector<shared_ptr<Jogo>> jogos = player->getJogos();
        unordered_set<string> idsJogos;

        for (const auto &jogo : jogos) {
            idsJogos.insert(jogo->getId());
        }

        for (auto idJogo : idJogosComprados){

            idJogo = leitor.limparCampoCSV(idJogo);
            if (!idJogo.empty())
            {
                auto jogo = tabelaJogos.busca(idJogo);
                if (jogo)
                {
                    if (idsJogos.find(jogo->getId()) == idsJogos.end())
                    {
                        jogos.push_back(jogo);
                        idsJogos.insert(jogo->getId());
                    }
                }
            }
        }
        if (player)
            player->setJogos(jogos); });
}

// Adiciona conquistas na tabela hash a partir de um arquivo CSV
void HashPlayers::adicionaConquistasNaHash(TabelaHash<Conquista> &tabelaConquistas)
{
    leitor.processarCSV(CSV_ACHIEVEMENTS_PATH, [&](const vector<string> &linha)
                        {
        string id = (linha.size() > 0 && !linha[0].empty()) ? linha[0] : "";
        string idJogo = (linha.size() > 1 && !linha[1].empty()) ? linha[1] : "";
        string titulo = (linha.size() > 2) ? linha[2] : "";
        string descricao = (linha.size() > 3) ? linha[3] : "";
        auto novaConquista = make_shared<Conquista>(id, idJogo, titulo, descricao);
        tabelaConquistas.insere(novaConquista); });
}

// Adiciona conquistas aos jogadores a partir de um arquivo CSV
void HashPlayers::adicionaConquistasNosPlayers(TabelaHash<Player> &tabelaJogadores, MetodoDeColisao metodoDeColisao)
{
    int totalConquistas = leitor.contadorCSV(CSV_ACHIEVEMENTS_PATH);
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
            player->addConquista(conquista); });
}

// Cria uma tabela hash que relaciona jogos e jogadores, onde cada jogo tem uma lista de jogadores que o possuem
void HashPlayers::criaHashJogosParaJogadores(TabelaHash<JogadoresDoJogo> &tabelaJogos, const TabelaHash<Player> &tabelaPlayers)
{
    int totalJogos = leitor.contadorCSV(CSV_GAMES_PATH);
    int tamanhoTabela = static_cast<int>(totalJogos);
    tamanhoTabela = static_cast<int>(ceil(tamanhoTabela / 0.7));
    tabelaJogos = TabelaHash<JogadoresDoJogo>(tamanhoTabela, MetodoDeColisao::ENCADEAMENTO);

    tabelaPlayers.forEach([&](const shared_ptr<Player> &player) {
        for (const auto &jogo : player->getJogos()) {
            if (jogo) {
                string idJogo = jogo->getId();
                auto jogadoresDoJogo = tabelaJogos.busca(idJogo);

                if (!jogadoresDoJogo) {
                    jogadoresDoJogo = make_shared<JogadoresDoJogo>();
                    jogadoresDoJogo->idJogo = idJogo;
                    tabelaJogos.insere(jogadoresDoJogo);
                }

                jogadoresDoJogo->addJogador(player->getId());
            }
        }
    });
}