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
    ArvoreB arvoreBJogos;
    ArvoreB arvoreBConquistas;

public: 
    Menu();

    void menuInicial();
    void menuArvoreB();
    void menuDeConsultas();
    
    void inicializarTabelaHash();
    void inicializarArvoreB();

    void menuBuscaHash();
    void menuInsercaoHash();
};

#endif