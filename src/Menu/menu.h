#ifndef MENU_H
#define MENU_H

#include "HashGenerico/hash_generico.h"
#include "../config.h"
#include "Objetos/Player.h"

class Menu
{
private:
    TabelaHash<Player> tabelaHash;

public: 
    Menu(); 
    void menuInicial();
    void inicializarTabelaHash();
    void menuHash();
    void menuArvoreB();

    void menuBuscaHash();
    void menuInsercaoHash();
};

#endif