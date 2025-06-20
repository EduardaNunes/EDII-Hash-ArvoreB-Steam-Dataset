#include <iostream>
#include "menu.h"

using namespace std;

void Menu::showMenu()
{
    int metodo;
    cout << "Escolha o metodo de tratamento de colisao:\n";
    cout << "1 - Encadeamento (Chaining)\n";
    cout << "2 - Enderecamento Aberto (Sondagem Linear)\n";
    cout << "Opcao: ";
    cin >> metodo;

    CollisionMethod metodoSelecionado = (metodo == 2) ? LINEAR_PROBING : CHAINING;

    Hash hash(10007, metodoSelecionado);
    hash.loadPlayers(CSV_PLAYERS_PATH);

    int opcao;
    do
    {
        cout << "\n=== MENU ===\n";
        cout << "1 - Buscar jogador por ID\n";
        cout << "2 - Remover jogador por ID\n";
        cout << "3 - Mostrar estatisticas\n";
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
        case 3:
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
