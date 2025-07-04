#include <iostream>
#include <fstream>
#include <stdexcept>
#include <limits>
#include <cmath>

#include "menu.h"
#include "./ArvoreB/arvoreB.h"
#include "./LeitorDePlanilha/leitorDePlanilha.h"

using namespace std;

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
            tabelaHash = hashColisoes(); 
            menuHash();
            break;
        }
        case 2:
        {
            menuArvoreB();
            break;
        }
        case 0:
            cout << "Saindo...\n";
            break;
        default:
            cout << "Opcao invalida.\n";
        }

    } while (opcao != 0);
}

PlayerHashTable Menu::hashColisoes()
{
    int metodoColisao;
    while (true)
    {
        cout << "Escolha o metodo de tratamento de colisao:\n";
        cout << "1 - Encadeamento (Chaining)\n";
        cout << "2 - Enderecamento Aberto (Sondagem Linear)\n";
        cout << "Opcao: ";
        cin >> metodoColisao;
        cout << "Criando... \n";
        
        if (!cin.fail() && (metodoColisao == 1 || metodoColisao == 2))
            break;

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Opcao invalida. Digite 1 ou 2.\n";
    }

    CollisionMethod estrategia = (metodoColisao == 2) ? CollisionMethod::LINEAR_PROBING : CollisionMethod::CHAINING;
    LeitorDePlanilha leitor;
    int totalJogadores = leitor.contadorCSV(CSV_PLAYERS_PATH);
    int tamanhoTabela = static_cast<int>(ceil(totalJogadores / 0.7));

    PlayerHashTable tabela(tamanhoTabela, estrategia);
    tabela.loadPlayersFromCSV(CSV_PLAYERS_PATH);

    return tabela;
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

        try {
            opcao = stoi(entrada);
        } catch (...) {
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
    ArvoreB arvoreB(64);

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
        try {
            opcao = stoi(entrada);
        } catch (...) {
            cout << "A opcao precisa ser numerica." << endl;
            continue;
        }

        switch (opcao)
        {
        case 1:
        {
            //arvoreB.indexarConquistas();
            LeitorDePlanilha leitor;
            vector<vector<string>> dados = leitor.lerCSV(CSV_PURCHASED_GAMES_TESTE_PATH);
            int linhaNum = 1;
            for (const auto& linha : dados) {
                cout << linhaNum++ << ": ";
                for (const auto& valor : linha) {
                    cout << valor << " | ";
                }
                cout << "\n";
            }
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

    Player* p = tabelaHash.findPlayerById(id);
    if (p) {
        cout << *p << endl;
    } else {
        cout << "Jogador nao encontrado.\n";
    }
}


void Menu::menuInsercaoHash()
{
    string id;
    string pais, dataCriacao;

    cout << "\n=== Inserir Jogador ===\n";
    cout << "Digite o ID do jogador: ";
    getline(cin, id);

    cout << "Digite o pais: ";
    getline(cin, pais);
    cout << "Digite a data de criacao (YYYY-MM-DD): ";
    getline(cin, dataCriacao);

    Player novoJogador(id, pais, dataCriacao);
    tabelaHash.insertPlayer(novoJogador);
    cout << "Jogador inserido com sucesso!\n";
}