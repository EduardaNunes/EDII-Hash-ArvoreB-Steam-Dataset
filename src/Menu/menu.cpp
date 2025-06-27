#include <iostream>
#include <fstream>
#include "menu.h"
#include "./ArvoreB/arvoreB.h"

using namespace std;

int contarJogadoresCSV(const string &caminho)
{
    ifstream file(caminho);
    string line;
    int count = 0;

    getline(file, line);

    while (getline(file, line))
    {
        if (!line.empty())
            count++;
    }

    return count;
}

void Menu::menuInicial(){

    int opcao;
    do{
        cout << "=== Menu Inicial ===" << endl;
        cout << "1 - Hash" << endl;
        cout << "2 - Arvore B" << endl;
        cout << "0 - Sair" << endl;
        cout << "Escolha: ";
        cin >> opcao;

        switch (opcao)
        {
        case 1:
        {
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

void Menu::menuHash(){
    int metodoColisao;
    cout << "Escolha o metodo de tratamento de colisao:\n";
    cout << "1 - Encadeamento (Chaining)\n";
    cout << "2 - Enderecamento Aberto (Sondagem Linear)\n";
    cout << "Opcao: ";
    cin >> metodoColisao;

    CollisionMethod estrategiaDeColisao = (metodoColisao == 2) ? CollisionMethod::LINEAR_PROBING : CollisionMethod::CHAINING;

    int totalJogadores = contarJogadoresCSV(CSV_PLAYERS_PATH);
    int tamanhoTabela = static_cast<int>(totalJogadores);

    PlayerHashTable tabelaJogadores(tamanhoTabela, estrategiaDeColisao);
    tabelaJogadores.loadPlayersFromCSV(CSV_PLAYERS_PATH);

    int opcaoMenu;
    do
    {
        cout << "\n=== MENU HASH ===\n";
        cout << "1 - Buscar jogador por ID\n";
        cout << "2 - Inserir novo jogador\n";
        cout << "3 - Remover jogador por ID\n";
        cout << "4 - Mostrar estatisticas\n";
        cout << "0 - Sair\n";
        cout << "Escolha: ";
        cin >> opcaoMenu;

        switch (opcaoMenu)
        {
        case 1:
        {
            long long id;
            cout << "Digite o ID do jogador: ";
            cin >> id;
            Player *p = tabelaJogadores.findPlayerById(id);
            if (p)
            {
                cout << *p << endl;
            }
            else
            {
                cout << "Jogador nao encontrado.\n";
            }
            break;
        }
        case 2:
        {
            long long id;
            string pais, dataCriacao;
            cout << "Digite o ID do jogador: ";
            cin >> id;
            cin.ignore();
            cout << "Digite o pais: ";
            getline(cin, pais);
            cout << "Digite a data de criacao (YYYY-MM-DD): ";
            getline(cin, dataCriacao);

            Player novoJogador(id, pais, dataCriacao);
            tabelaJogadores.insertPlayer(novoJogador);
            cout << "Jogador inserido com sucesso!\n";
            break;
        }
        case 3:
        {
            long long id;
            cout << "Digite o ID do jogador a remover: ";
            cin >> id;
            if (tabelaJogadores.removePlayerById(id))
            {
                cout << "Jogador removido com sucesso.\n";
            }
            else
            {
                cout << "Jogador nao encontrado.\n";
            }
            break;
        }
        case 4:
            tabelaJogadores.exibirEstatisticas();
            break;
        case 0:
            cout << "Saindo...\n";
            break;
        default:
            cout << "Opcao invalida.\n";
        }

    } while (opcaoMenu != 0);
}

void Menu::menuArvoreB(){

    ArvoreB arvoreB;

    int opcao;
    do
    {
        cout << "=== Menu Arvore B ===" << endl;
        cout << "1 - Indexar por conquistas" << endl;
        cout << "2 - Indexar por jogos" << endl;
        cout << "0 - Voltar" << endl;
        cout << "Escolha: ";
        cin >> opcao;

        switch (opcao)
        {
        case 1:
        {
            arvoreB.indexarConquistas();
            break;
        }
        case 2:
        {
            arvoreB.indexarJogos();
            break;
        }
        case 0:
            cout << "Voltando...\n";
            Menu::menuInicial();
            break;
        default:
            cout << "Opcao invalida.\n";
        }

    } while (opcao != 0); 
}