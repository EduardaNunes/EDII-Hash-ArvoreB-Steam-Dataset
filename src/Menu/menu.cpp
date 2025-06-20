#include <iostream>
#include "menu.h"

using namespace std;

void Menu::showMenu() {
    hash.loadPlayers();

    int opcao;
    do {
        cout << "\n=== MENU ===\n";
        cout << "1 - Buscar jogador por ID" << endl;
        cout << "2 - Mostrar top N jogadores" << endl;
        cout << "0 - Sair" << endl;
        cout << "Escolha: ";
        cin >> opcao;

        switch (opcao) {
        case 1: {
            long long id;
            cout << "Digite o ID do jogador: ";
            cin >> id;
            Player* p = hash.searchById(id);
            if (p) {
                cout << *p << endl;
            } else {
                cout << "Jogador não encontrado.\n";
            }
            break;
        }
        case 2:
            cout << "Funcionalidade ainda não implementada.\n";
            break;
        case 0:
            cout << "Saindo...\n";
            break;
        default:
            cout << "Opção inválida.\n";
        }
    } while (opcao != 0);
}
