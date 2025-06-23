#include <iostream>
#include <fstream>
#include "menu.h"

using namespace std;

int contarJogadoresCSV(const string& caminho) {
    ifstream file(caminho);
    string line;
    int count = 0;

    getline(file, line); 

    while (getline(file, line)) {
        if (!line.empty()) count++;
    }

    return count;
}

void Menu::showMenu()
{
    int metodo;
    cout << "Escolha o metodo de tratamento de colisao:\n";
    cout << "1 - Encadeamento (Chaining)\n";
    cout << "2 - Enderecamento Aberto (Sondagem Linear)\n";
    cout << "Opcao: ";
    cin >> metodo;

    CollisionMethod metodoSelecionado = (metodo == 2) ? LINEAR_PROBING : CHAINING;

    int totalJogadores = contarJogadoresCSV(CSV_PLAYERS_PATH);
    int tamanhoTabela = static_cast<int>(totalJogadores * 1.3);

    Hash hash(tamanhoTabela, metodoSelecionado);
    hash.loadPlayers(CSV_PLAYERS_PATH);

    int opcao;
    do
    {
        cout << "\n=== MENU ===\n";
        cout << "1 - Buscar jogador por ID\n";
        cout << "2 - Inserir novo jogador\n";
        cout << "3 - Remover jogador por ID\n";
        cout << "4 - Mostrar estatisticas\n";
        cout << "0 - Sair\n";
        cout << "Escolha: ";
        cin >> opcao;

        switch (opcao)
        {
        case 1:
        {
            long long id;
            cout << "Digite o ID do jogador: ";
            cin >> id;
            Player *p = hash.searchById(id);
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
            string country, created;
            cout << "Digite o ID do jogador: ";
            cin >> id;
            cin.ignore(); 
            cout << "Digite o pais: ";
            getline(cin, country);
            cout << "Digite a data de criacao (YYYY-MM-DD): ";
            getline(cin, created);

            Player novo(id, country, created);
            hash.insert(novo);
            cout << "Jogador inserido com sucesso!\n";
            break;
        }
        case 3:
        {
            long long id;
            cout << "Digite o ID do jogador a remover: ";
            cin >> id;
            if (hash.remove(id))
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
            hash.printStats();
            break;
        case 0:
            cout << "Saindo...\n";
            break;
        default:
            cout << "Opcao invalida.\n";
        }

    } while (opcao != 0);
}
