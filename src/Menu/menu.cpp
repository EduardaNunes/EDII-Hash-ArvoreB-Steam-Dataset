#include <iostream>
#include "menu.h"

using namespace std;

void Menu::showMenu()
{
    int opcao;

    do
    {
        cout << "1 - Buscar jogador por ID" << endl;
        cout << "2 - Mostrar top N jogadores" << endl;
        cout << "0 - Sair" << endl;
        cin >> opcao;

        switch (opcao)
        {
        case 1: /* chama busca na hash */
            break;
        case 2: /* busca na árvore B */
            break;
        }
    } while (opcao != 0);
}