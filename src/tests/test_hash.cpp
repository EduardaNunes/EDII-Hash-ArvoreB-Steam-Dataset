#include <cassert>
#include <iostream>
#include <fstream>
#include "../src/Hash/hash.h"

using namespace std;

void testInsercaoBuscaRemocao()
{
    PlayerHashTable tabela(7, CollisionMethod::CHAINING);

    Player p1(1, "BR", "2023-01-01");
    Player p2(2, "US", "2022-05-05");

    tabela.insertPlayer(p1);
    tabela.insertPlayer(p2);

    Player *found1 = tabela.findPlayerById(1);
    assert(found1 != nullptr && "Jogador com ID 1 deveria estar presente.");

    Player *found2 = tabela.findPlayerById(2);
    assert(found2 != nullptr && "Jogador com ID 2 deveria estar presente.");
    assert(found2->country == "US" && "Pais do jogador com ID 2 deveria ser 'US'.");

    assert(tabela.removePlayerById(1) && "Remocao do jogador com ID 1 deveria retornar true.");
    assert(tabela.findPlayerById(1) == nullptr && "Jogador com ID 1 nao deveria estar mais presente.");
}

void testColisaoChaining()
{
    PlayerHashTable tabela(2, CollisionMethod::CHAINING);

    Player p1(1, "A", "2022");
    Player p2(3, "B", "2023");

    tabela.insertPlayer(p1);
    tabela.insertPlayer(p2);

    Player *found1 = tabela.findPlayerById(1);
    assert(found1 != nullptr && "Jogador com ID 1 deveria estar presente apos colisao.");

    Player *found2 = tabela.findPlayerById(3);
    assert(found2 != nullptr && "Jogador com ID 3 deveria estar presente apos colisao.");
}

void testRehashProbing()
{
    PlayerHashTable tabela(3, CollisionMethod::LINEAR_PROBING); // Capacidade inicial pequena

    for (int i = 0; i < 10; i++)
    {
        tabela.insertPlayer(Player(i, "XX", "2000-01-01"));
    }

    for (int i = 0; i < 10; i++)
    {
        Player *found = tabela.findPlayerById(i);
        assert(found != nullptr && "Jogador deveria estar presente apos rehash.");
        assert(found->playerId == i && "ID do jogador encontrado nao bate com o inserido.");
    }
}

void testRehashChaining()
{
    PlayerHashTable tabela(3, CollisionMethod::CHAINING);

    for (int i = 0; i < 10; i++)
    {
        tabela.insertPlayer(Player(i, "YY", "2010-01-01"));
    }

    for (int i = 0; i < 10; i++)
    {
        Player *found = tabela.findPlayerById(i);
        assert(found != nullptr && "Jogador deveria estar presente apos rehash chaining.");
        assert(found->playerId == i && "ID do jogador encontrado nao bate com o inserido.");
    }
}

void testAtualizacaoJogadorExistente()
{
    PlayerHashTable tabela(7, CollisionMethod::CHAINING);

    Player p1(1, "BR", "2023-01-01");
    tabela.insertPlayer(p1);

    Player p1_update(1, "US", "2024-02-02");
    tabela.insertPlayer(p1_update);

    Player *found = tabela.findPlayerById(1);
    assert(found != nullptr && "Jogador com ID 1 deveria estar presente.");
    assert(found->country == "US" && "Pais do jogador atualizado deveria ser 'US'.");
    assert(found->created == "2024-02-02" && "Data de criacao deveria ser atualizada.");
}

void testEstatisticas()
{
    PlayerHashTable tabela(5, CollisionMethod::CHAINING);

    assert(tabela.findPlayerById(10) == nullptr);

    tabela.insertPlayer(Player(1, "A", "d1"));
    tabela.insertPlayer(Player(6, "B", "d2"));

    tabela.exibirEstatisticas();
}

// Testa comportamento após remoção em sondagem linear (procura e inserção)
void testRemocaoProbing()
{
    PlayerHashTable tabela(5, CollisionMethod::LINEAR_PROBING);

    tabela.insertPlayer(Player(1, "A", "d1"));
    tabela.insertPlayer(Player(6, "B", "d2")); // Deve causar colisão na posição 1

    assert(tabela.removePlayerById(1));
    assert(tabela.findPlayerById(1) == nullptr);

    tabela.insertPlayer(Player(11, "C", "d3"));
    Player *found = tabela.findPlayerById(11);
    assert(found != nullptr && "Jogador inserido após remoção deveria ser encontrado.");
}

void testLoadPlayersFromCSV()
{
    const string fileName = "temp_players.csv";
    ofstream file(fileName);
    file << "playerid,country,created\n";
    file << "100,BR,2021-01-01\n";
    file << "101,US,2022-02-02\n";
    file.close();

    PlayerHashTable tabela(10, CollisionMethod::CHAINING);
    tabela.loadPlayersFromCSV(fileName);

    Player *p100 = tabela.findPlayerById(100);
    Player *p101 = tabela.findPlayerById(101);

    assert(p100 != nullptr && "Jogador 100 deveria estar presente apos carregar CSV.");
    assert(p101 != nullptr && "Jogador 101 deveria estar presente apos carregar CSV.");

    remove(fileName.c_str());
}

void testIDsInvalidos()
{
    PlayerHashTable tabela(5, CollisionMethod::CHAINING);

    tabela.insertPlayer(Player(-42, "?", "2021-11-11"));
    Player *found = tabela.findPlayerById(-42);
    assert(found == nullptr && "IDs negativos não devem ser permitidos.");

    assert(!tabela.removePlayerById(9999999) && "Remocao de ID inexistente deveria retornar false.");
    assert(tabela.findPlayerById(9999999) == nullptr && "ID inexistente nao deveria ser encontrado.");
}

int main()
{
    try
    {
        testInsercaoBuscaRemocao();
        testColisaoChaining();
        testRehashProbing();
        testRehashChaining();
        testAtualizacaoJogadorExistente();
        testEstatisticas();
        testRemocaoProbing();
        testLoadPlayersFromCSV();
        testIDsInvalidos();

        cout << "Todos os testes passaram com sucesso!\n";
        return 0;
    }
    catch (const std::exception &e)
    {
        cerr << "Excecao capturada: " << e.what() << "\n";
        return 1;
    }
    catch (...)
    {
        cerr << "Erro desconhecido ocorreu durante os testes!\n";
        return 2;
    }
}
