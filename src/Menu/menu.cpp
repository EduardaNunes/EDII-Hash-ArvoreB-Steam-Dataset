#include <iostream>
#include <fstream>
#include <stdexcept>
#include <limits>
#include <cmath>
#include <vector>

#include "menu.h"

using namespace std;

Menu::Menu() : tabelaHash(1, MetodoDeColisao::ENCADEAMENTO), arvoreB(64) {}

void Menu::menuInicial()
{
    int opcao;
    do
    {
        cout << "=== Menu Inicial ===" << endl;
        cout << "1 - Hash" << endl;
        cout << "2 - Arvore B" << endl;
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
            inicializarTabelaHash();
            menuHash();
            break;
        }
        case 2:
            menuArvoreB();
            break;
        case 0:
            cout << "Saindo...\n";
            break;
        default:
            cout << "Opcao invalida.\n";
        }

    } while (opcao != 0);
}

void Menu::menuDeConsultas()
{
    string entrada, id, minStr, maxStr;
    int opcao, min, max;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    do
    {
        cout << "\n=== Menu Consultas ===\n";
        cout << "1 - Buscar jogador\n";
        cout << "2 - Listar jogadores com mais conquistas\n";
        cout << "3 - Listar jogos de um jogador\n";
        cout << "4 - Mostrar top N jogadores com mais conquistas\n";
        cout << "5 - Mostrar jogadores entre um intervalo de conquistas\n";
        cout << "6 - Buscar jogadores que possuem determinado jogo\n";
        cout << "7 - Estatísticas\n";
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
            // adicionar aqui a função
            break;
        case 3:
            cout << "Digite o ID do jogador: ";
            getline(cin, id);
            // podemos usar a hash porque o player tem um getJogos (só uma ideia)
            break;
        case 4:
            // adicionar aqui a função
            break;
        case 5:
            cout << "Digite o número mínimo de conquistas: ";
            getline(cin, minStr);
            cout << "Digite o número máximo de conquistas: ";
            getline(cin, maxStr);
            try
            {
                min = stoi(minStr);
                max = stoi(maxStr);
            }
            catch (...)
            {
                cout << "O minimo e maximo precisam ser numericos." << endl;
                continue;
            }
            // adicionar aqui a função
            break;
        case 6:
            cout << "Digite o id do jogo: ";
            getline(cin, id);
            // adicionar aqui a função
            break;
        case 7:
            // adicionar aqui a função
            break;
        case 0:
            cout << "Voltando...\n";
            break;
        default:
            cout << "Opcao invalida.\n";
        }

    } while (opcao != 0);
}

void Menu::inicializarTabelaHash()
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

    // LeitorDePlanilha leitor;
    // int totalJogadores = leitor.contadorCSV(CSV_PLAYERS_PATH);
    // int tamanhoTabela = static_cast<int>(ceil(totalJogadores / 0.7));

    // this->tabelaHash = TabelaHash<Player>(tamanhoTabela, estrategia);

    // vector<vector<string>> dados = leitor.lerCSV(CSV_PLAYERS_PATH);
    // for (size_t i = 1; i < dados.size(); i++)
    // {
    //     if (dados[i].size() >= 3 && !dados[i][0].empty())
    //     {
    //         Player p(dados[i][0], dados[i][1], dados[i][2]);
    //         this->tabelaHash.insere(p);
    //     }
    // }
    HashPlayers tabelaPlayers;
    this->tabelaHash = tabelaPlayers.criaHashDePlayers(estrategia);
    cout << "Tabela criada e jogadores carregados!\n";
}

void Menu::menuHash()
{
    string entrada;
    int opcao;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    do
    {
        cout << "\n=== Menu Hash ===\n";
        cout << "1 - Buscar jogador\n";
        cout << "2 - Inserir jogador\n";
        cout << "3 - Mostrar estatisticas\n";
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
            menuInsercaoHash();
            break;
        case 3:
            tabelaHash.exibirEstatisticas();
            break;
        case 0:
            cout << "Voltando...\n";
            break;
        default:
            cout << "Opcao invalida.\n";
        }

    } while (opcao != 0);
}

void Menu::menuArvoreB()
{

    string entrada;
    int opcao;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    do
    {
        cout << "=== Menu Arvore B ===" << endl;
        cout << "1 - Indexar por conquistas" << endl;
        cout << "2 - Indexar por jogos" << endl;
        cout << "0 - Voltar" << endl;
        cout << "Escolha: ";
        string entrada;
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
        {
            break;
        }
        case 2:
        {
            arvoreB.indexarJogos();
            break;
        }
        case 0:
            cout << "Voltando...\n";
            break;
        default:
            cout << "Opcao invalida.\n";
        }

    } while (opcao != 0);
}

void Menu::menuBuscaHash()
{
    string id;

    cout << "\n=== Buscar Jogador ===\n";
    cout << "Digite o ID do jogador: ";
    getline(cin, id);

    auto p = tabelaHash.busca(id); // agora é shared_ptr<Player>
    if (p)
    {
        cout << *p << endl;
    }
    else
    {
        cout << "Jogador nao encontrado.\n";
    }
}

void Menu::menuInsercaoHash()
{
    string id, pais, dataCriacao;

    cout << "\n=== Inserir Jogador ===\n";
    cout << "Digite o ID do jogador: ";
    getline(cin, id);

    Utils utils;
    if (!utils.verificaIdJogador(id))
    {
        cout << "ID de jogador invalido! \n É preciso que ele tenha 17 digitos numericos" << endl;
        menuInsercaoHash();
    }
    else if (tabelaHash.busca(id) != nullptr)
    {
        cout << "Jogador já existente!" << endl;
        menuInsercaoHash();
    }

    cout << "Digite o pais: ";
    getline(cin, pais);
    cout << "Digite a data de criacao (YYYY-MM-DD): ";
    getline(cin, dataCriacao);

    auto novoJogador = make_shared<Player>(id, pais, dataCriacao);
    tabelaHash.insere(novoJogador);
    cout << "Jogador inserido com sucesso!\n";
}