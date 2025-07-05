#ifndef MENU_H
#define MENU_H

#include "../LeitorDePlanilha/leitorDePlanilha.h"
#include "../HashGenerico/hash_generico.h"
#include "../HashGenerico/hash_players.h"
#include "../Objetos/Player.h"
#include "../ArvoreB/arvoreB.h"
#include "../Utils/utils.h"
#include "../config.h"

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