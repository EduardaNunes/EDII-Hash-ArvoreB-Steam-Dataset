#ifndef MENU_H
#define MENU_H

#include "Hash/hash.h"
#include "../config.h"

class Menu
{
private:
    PlayerHashTable tabelaHash;

public:
    void menuInicial();
    PlayerHashTable hashColisoes();
    void menuHash(PlayerHashTable& tabelaJogadores);
    void menuArvoreB();
};

#endif
