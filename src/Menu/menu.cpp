#include <iostream>
#include <fstream>
#include <stdexcept>
#include <limits>
#include <cmath>
#include <vector>
#include <unordered_map>
#include <iomanip>

#include "menu.h"

using namespace std;

// Construtor da classe Menu, inicializa as tabelas hash e a árvore B
Menu::Menu() : tabelaHash(1, MetodoDeColisao::ENCADEAMENTO), hashJogos(1, MetodoDeColisao::ENCADEAMENTO), arvoreBJogos(64), arvoreBConquistas(64) {}

// menuInicial é o ponto de entrada do programa, onde o usuário pode escolher opções para interagir com o sistema
void Menu::menuInicial()
{
    inicializarTabelaHashPlayers();
    inicializarTabelaHashJogos();
    inicializarArvoreB();

    int opcao;
    do
    {
        cout << "\n=== Menu Inicial ===" << endl;
        cout << "1 - Inserir novo jogador" << endl;
        cout << "2 - Abrir o menu de consultas" << endl;
        cout << "3 - Exibir estatisticas da Hash" << endl;
        cout << "0 - Sair" << endl;
        cout << "Escolha: ";
        cin >> opcao;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "A opcao precisa ser numerica." << endl;
            continue;
        }

        switch (opcao)
        {
        case 1:
        {
            menuInsercaoHash();
            break;
        }
        case 2:
            menuDeConsultas();
            break;
        case 3:
            tabelaHash.exibirEstatisticas();
            break;
        case 0:
            cout << "Saindo...\n";
            break;
        default:
            cout << "Opcao invalida.\n";
        }

    } while (opcao != 0);
}

// menuDeConsultas exibe um menu com opções de consultas sobre jogadores, jogos e conquistas
void Menu::menuDeConsultas()
{
    string entrada, id, minStr, maxStr, quantidadeTop;
    int opcao, min, max, quantidade;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    do
    {
        cout << "\n=== Menu Consultas ===\n";
        cout << " 1 - Buscar jogador\n";
        cout << " 2 - Listar jogos de um jogador\n";
        cout << " 3 - Listar conquistas de um jogador\n";
        cout << " 4 - Listar top N jogadores com mais jogos\n";
        cout << " 5 - Listar top N jogadores com mais conquistas\n";
        cout << " 6 - Mostrar jogadores entre um intervalo de jogos\n";
        cout << " 7 - Mostrar jogadores entre um intervalo de conquistas\n";
        cout << " 8 - Buscar jogadores que possuem determinado jogo\n";
        cout << " 9 - Mostrar Top N jogos adquiridos\n";
        cout << "10 - Estatisticas do sistema\n";
        cout << "0 - Voltar\n";
        cout << "Escolha: ";
        getline(cin, entrada);

        try
        {
            opcao = stoi(entrada);
        }
        catch (...)
        {
            cout << "A opcao precisa ser numerica." << endl;
            continue;
        }

        switch (opcao)
        {
        case 1:
            menuBuscaHash();
            break;
        case 2:
                cout << "\nDigite o ID do jogador: ";
                getline(cin, id);

                imprimeJogosOuConquistasDoJogador(id, TipoDeIndexacao::JOGOS);
            break;
        case 3:
                cout << "\nDigite o ID do jogador: ";
                getline(cin, id);

                imprimeJogosOuConquistasDoJogador(id, TipoDeIndexacao::CONQUISTAS);
            break;
        case 4:
            while (true) {
                cout << "\nDigite a quantidade do top a ser buscado: ";
                getline(cin, quantidadeTop);
                try {
                    quantidade = stoi(quantidadeTop);
                    if (quantidade <= 0) {
                        cout << "A quantidade deve ser um numero positivo.\n";
                        continue;
                    }
                } catch (...) {
                    cout << "A quantidade do top precisa ser numerica.\n";
                    continue;
                }
                break;
            }
            imprimeTopJogadores(quantidade, TipoDeIndexacao::JOGOS);
            break;
        case 5:
            while (true) {
                cout << "\nDigite a quantidade do top a ser buscado: ";
                getline(cin, quantidadeTop);
                try {
                    quantidade = stoi(quantidadeTop);
                    if (quantidade <= 0) {
                        cout << "A quantidade deve ser um nemero positivo.\n";
                        continue;
                    }
                } catch (...) {
                    cout << "A quantidade do top precisa ser numerica.\n";
                    continue;
                }
                break;
            }
            imprimeTopJogadores(quantidade, TipoDeIndexacao::CONQUISTAS);
            break;
        case 6:
            while (true) {
                cout << "Digite o numero minimo de jogos: ";
                getline(cin, minStr);
                cout << "Digite o numero maximo de jogos: ";
                getline(cin, maxStr);
                try {
                    min = stoi(minStr);
                    max = stoi(maxStr);
                    if (min < 0 || max < 0) {
                        cout << "Os valores minimo e maximo devem ser positivos.\n";
                        continue;
                    }
                    if (min > max) {
                        cout << "O valor minimo nao pode ser maior que o maximo.\n";
                        continue;
                    }
                } catch (...) {
                    cout << "O minimo e maximo precisam ser numericos.\n";
                    continue;
                }
                break;
            }
            imprimeIntervaloDeJogadores(min, max, TipoDeIndexacao::JOGOS);
            break;
        case 7:
            while (true) {
                cout << "Digite o numero minimo de conquistas: ";
                getline(cin, minStr);
                cout << "Digite o numero maximo de conquistas: ";
                getline(cin, maxStr);
                try {
                    min = stoi(minStr);
                    max = stoi(maxStr);
                    if (min < 0 || max < 0) {
                        cout << "Os valores minimo e maximo devem ser positivos.\n";
                        continue;
                    }
                    if (min > max) {
                        cout << "O valor minimo nao pode ser maior que o maximo.\n";
                        continue;
                    }
                } catch (...) {
                    cout << "O minimo e maximo precisam ser numericos.\n";
                    continue;
                }
                break;
            }
            imprimeIntervaloDeJogadores(min, max, TipoDeIndexacao::CONQUISTAS);
            break;
        case 8:
            cout << "Digite o id do jogo: ";
            getline(cin, id);
            imprimeJogadoresDoJogo(id);
            break;
        case 9:
            cout << "\nDigite a quantidade do top a ser buscado: ";
            getline(cin, quantidadeTop);

            try
            {
                quantidade = stoi(quantidadeTop);
            }
            catch (...)
            {
                cout << "A quantidade do top precisa ser numericos." << endl;
                continue;
            }
            imprimeTopJogos(quantidade);
            break;
        case 10:
            cout << "Calculando estatisticas do sistema...\n";
            imprimeEstatisticasJogos();
            break;
        case 0:
            cout << "Voltando...\n";
            break;
        default:
            cout << "Opcao invalida.\n";
        }

    } while (opcao != 0);
}

// Inicializa a tabela hash de jogadores com dados pré-carregados
void Menu::inicializarTabelaHashPlayers()
{
    int metodoColisao;
    while (true)
    {
        cout << "Escolha o metodo de tratamento de colisao:\n";
        cout << "1 - Encadeamento (Chaining)\n";
        cout << "2 - Enderecamento Aberto (Sondagem Linear)\n";
        cout << "Opcao: ";
        cin >> metodoColisao;

        if (!cin.fail() && (metodoColisao == 1 || metodoColisao == 2))
            break;

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Opcao invalida. Digite 1 ou 2.\n";
    }

    cout << "Criando tabela hash...\n";

    MetodoDeColisao estrategia = (metodoColisao == 1) ? MetodoDeColisao::ENCADEAMENTO : MetodoDeColisao::SONDAGEM_LINEAR;

    HashPlayers geradorDePlayers;

    geradorDePlayers.populaTabelaComPlayers(this->tabelaHash, estrategia);
    cout << "Tabela criada e jogadores carregados!\n";
}

// Inicializa a tabela hash de jogos com dados pré-carregados
void Menu::inicializarTabelaHashJogos()
{
    cout << "Criando tabela hash para jogos...\n";
    HashPlayers hashPlayersUtil;
    hashPlayersUtil.criaHashJogosParaJogadores(hashJogos, tabelaHash);
    cout << "Tabela hash de jogos criada com sucesso!\n";
}

// Inicializa a árvore B com os jogadores indexados por jogos e conquistas
void Menu::inicializarArvoreB()
{
    cout << "Indexando jogadores por quantidade de jogos na Arvore B...\n";
    arvoreBJogos.indexarPorJogos(tabelaHash);

    cout << "Indexando jogadores por quantidade de conquistas na Arvore B...\n";
    arvoreBConquistas.indexarPorConquistas(tabelaHash);

    cout << "Arvores B construidas com sucesso!\n";
}

// menuBuscaHash permite ao usuário buscar um jogador pelo ID
void Menu::menuBuscaHash()
{
    string id;

    cout << "\n=== Buscar Jogador ===\n";
    cout << "Digite o ID do jogador: ";
    getline(cin, id);

    auto p = tabelaHash.busca(id);
    if (p)
    {
        cout << *p << endl;
    }
    else
    {
        cout << "Jogador nao encontrado.\n";
    }
}

// menuInsercaoHash permite ao usuário inserir um novo jogador na tabela hash
void Menu::menuInsercaoHash()
{
    string id, pais;
    Utils utils;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "\n=== Inserir Jogador ===\n";

    while (true)
    {
        cout << "Digite o ID do jogador: (para voltar ao menu anterior, digite '0')";
        getline(cin, id);

        if (id == "0")
        {
            cout << "Voltando ao menu anterior...\n";
            return;
        }

        if (!utils.verificaIdJogador(id))
        {
            cout << "ID de jogador invalido! E preciso que ele tenha 17 digitos numericos.\n";
            continue;
        }

        if (tabelaHash.busca(id) != nullptr)
        {
            cout << "Jogador com este ID ja existe!\n";
            continue;
        }

        break;
    }

    cout << "Digite o pais: ";
    getline(cin, pais);

    auto novoJogador = make_shared<Player>(id, pais);

    tabelaHash.insere(novoJogador);
    cout << "Jogador inserido com sucesso!\n";
}

// imprimeTopJogadores exibe os top N jogadores com mais jogos ou conquistas, dependendo do tipo de indexação
void Menu::imprimeTopJogadores(int quantidade, TipoDeIndexacao tipo)
{

    vector<shared_ptr<Player>> topJogadores;

    if (tipo == TipoDeIndexacao::JOGOS)
    {
        topJogadores = arvoreBJogos.buscaTopJogadores(quantidade);
    }

    else if (tipo == TipoDeIndexacao::CONQUISTAS)
    {
        topJogadores = arvoreBConquistas.buscaTopJogadores(quantidade);
    }

    else
    {
        cout << "Tipo de indexacao invalido!" << endl;
        return;
    }

    cout << "\n========================================= TOP " << quantidade << " JOGADORES =========================================\n";
    cout << left
        << setw(4)  << ""
        << setw(23) << "ID"
        << setw(25) << "Pais"
        << setw(22) << "DataCriacao"
        << setw(10) << "Jogos"
        << "Conquistas" << endl;

    cout << string(100, '-') << endl;


    for (int i = 0; i < static_cast<int>(topJogadores.size()); ++i) {
        const auto& jogador = topJogadores[i];
        if (!jogador) continue;

        cout << setw(4)  << (i + 1)
            << setw(23) << jogador->getId()
            << setw(25) << jogador->getPais()
            << setw(22) << jogador->getDataDeCriacao()
            << setw(10) << jogador->getJogos().size()
            << jogador->getConquistas().size() << endl;

    }

    cout << string(100, '=') << "\n";

}

// imprimeIntervaloDeJogadores exibe jogadores dentro de um intervalo de jogos ou conquistas, dependendo do tipo de indexação
void Menu::imprimeIntervaloDeJogadores(int min, int max, TipoDeIndexacao tipo)
{

    vector<shared_ptr<Player>> intervaloDeJogadores;

    switch (tipo)
    {
    case TipoDeIndexacao::JOGOS:
        intervaloDeJogadores = arvoreBJogos.buscaPorIntervalo(min, max);
        break;

    case TipoDeIndexacao::CONQUISTAS:
        intervaloDeJogadores = arvoreBConquistas.buscaPorIntervalo(min, max);
        break;
    default:
        cout << "Tipo de indexacao invalido!" << endl;
        return;
    }

    cout << "\n=========== JOGADORES NO INTERVALO ============\n";

    for (size_t i = 0; i < intervaloDeJogadores.size(); ++i) {
        const auto& jogador = intervaloDeJogadores[i];
        if (!jogador) continue;

        cout << " " << setw(2) << (i + 1) << ". "
             << setw(25) << left << jogador->getId();

        if (tipo == TipoDeIndexacao::JOGOS) {
            cout << "| Qtd Jogos: " << jogador->getJogos().size();
        } else if (tipo == TipoDeIndexacao::CONQUISTAS) {
            cout << "| Qtd Conquistas: " << jogador->getConquistas().size();
        }

        cout << endl;
    }

    cout << "================================================\n";
    cout << "Total de jogadores encontrados: " << intervaloDeJogadores.size() << "\n";
    cout << "================================================\n";

}

// imprimeEstatisticasJogos exibe estatísticas gerais do sistema, como média de jogos e conquistas por jogador, e ranking de países com mais jogadores
void Menu::imprimeEstatisticasJogos() {
    int totalJogadores = 0;
    int totalJogos = 0;
    int totalConquistas = 0;
    unordered_map<string, int> jogadoresPorPais;

    tabelaHash.forEach([&](const shared_ptr<Player>& player) {
        if (!player) return;

        string pais = player->getPais();
        if (!pais.empty()) {
            jogadoresPorPais[pais]++;
        }

        totalJogadores++;

        const auto& jogos = player->getJogos();
        totalJogos += static_cast<int>(jogos.size());

        const auto& conquistas = player->getConquistas();
        totalConquistas += static_cast<int>(conquistas.size());
    });

    double mediaJogos = totalJogadores > 0 ? static_cast<double>(totalJogos) / totalJogadores : 0;
    double mediaConquistas = totalJogadores > 0 ? static_cast<double>(totalConquistas) / totalJogadores : 0;

    cout << "\n=========== ESTATISTICAS GERAIS ===========\n";
    cout << fixed << setprecision(2);
    cout << " - Media de jogos por jogador:      " << mediaJogos << endl;
    cout << " - Media de conquistas por jogador: " << mediaConquistas << endl;
    cout << "===========================================\n";

    vector<pair<string, int>> rankingPaises(jogadoresPorPais.begin(), jogadoresPorPais.end());
    sort(rankingPaises.begin(), rankingPaises.end(), [](const auto& a, const auto& b) {
        return b.second < a.second;
    });

    cout << "\n====== TOP 5 PAISES COM MAIS JOGADORES ======\n";
    for (int i = 0; i < min(5, static_cast<int>(rankingPaises.size())); ++i) {
        cout << " " << setw(2) << (i + 1) << ". "
            << setw(20) << left << rankingPaises[i].first
            << "| Jogadores: " << rankingPaises[i].second << endl;
    }
    cout << "=============================================\n";

}

// imprimeTopJogos exibe os jogos mais adquiridos, mostrando o título e a quantidade de jogadores que os possuem
void Menu::imprimeTopJogos(int quantidade) {

    unordered_map<string, pair<string, int>> jogoFrequencia;  // id -> {titulo, contagem}

    tabelaHash.forEach([&](const shared_ptr<Player>& player) {
        if (!player) return;

        const auto& jogos = player->getJogos();

        for (const auto& jogo : jogos) {
            if (!jogo) continue;
            string id = jogo->getId();
            string titulo = jogo->getTitulo();

            auto& entrada = jogoFrequencia[id];
            entrada.first = titulo;      // título
            entrada.second += 1;         // contagem
        }
    });

    // Converte para vetor e ordena por contagem
    vector<pair<string, int>> ranking; // {titulo, contagem}
    for (const auto& par : jogoFrequencia) {
        ranking.emplace_back(par.second.first, par.second.second);
    }

    sort(ranking.begin(), ranking.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });

    cout << "\n============== TOP JOGOS ADQUIRIDOS ============\n";
    for (int i = 0; i < min(quantidade, static_cast<int>(ranking.size())); ++i) {
        cout << " " << setw(2) << (i + 1) << ". "
            << setw(45) << left << ranking[i].first
            << "| Jogadores: " << ranking[i].second << endl;
    }
    cout << "================================================\n";
}

// imprimeJogadoresDoJogo exibe os jogadores que possuem um determinado jogo, identificado pelo ID
void Menu::imprimeJogadoresDoJogo(const string &id)
{
    auto p = hashJogos.busca(id);
    if (p && !p->jogadores.empty())
    {
        p->imprimeJogadores();
    }
    else
    {
        cout << "Nenhum jogador possui este jogo ou jogo nao encontrado.\n";
    }
}

// imprimeJogosOuConquistasDoJogador exibe os jogos ou conquistas de um jogador, dependendo do tipo de indexação
void Menu::imprimeJogosOuConquistasDoJogador(const string& id, TipoDeIndexacao tipo)
{
    auto p = tabelaHash.busca(id);

    if (!p)
    {
        cout << "\nJogador não encontrado.\n";
        return;
    }

    if (tipo == TipoDeIndexacao::JOGOS)
    {
        auto jogos = p->getJogos();

        if (jogos.empty())
        {
            cout << "\nO jogador não possui jogos cadastrados.\n";
            return;
        }

        cout << endl << string(41, '=') << "JOGOS DO JOGADOR" << string(41, '=') << endl;
        cout << left << setw(4) << "Titulo" <<  endl;
        cout << string(100, '-') << endl;

        for (size_t i = 0; i < jogos.size(); ++i)
        {
            if (jogos[i])
            {
                cout << setw(4) << (i + 1) << " "
                     <<  jogos[i]->getTitulo() << endl;
            }
        }

        cout << string(100, '=') << endl;
        cout << "Total de jogos: " << jogos.size() << endl;
        cout << string(100, '=') << endl;
    }
    else if (tipo == TipoDeIndexacao::CONQUISTAS)
    {
        auto conquistas = p->getConquistas();

        if (conquistas.empty())
        {
            cout << "\nO jogador não possui conquistas cadastradas.\n";
            return;
        }

        cout << endl << string(48, '=') << "CONQUISTAS DO JOGADOR" << string(49, '=') << endl;
        cout << left << setw(4) << "Nome da Conquista" << endl;
        cout << string(100, '-') << endl;

        for (size_t i = 0; i < conquistas.size(); ++i)
        {
            cout << setw(4) << (i + 1) << " "
                 << conquistas[i]->getTitulo() << endl;
        }

        cout << string(100, '=') << endl;
        cout << "Total de conquistas: " << conquistas.size() << endl;
        cout << string(100, '=') << endl;
    }
}