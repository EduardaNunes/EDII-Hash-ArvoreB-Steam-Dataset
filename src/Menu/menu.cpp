#include <iostream>
#include <fstream>
#include <stdexcept>
#include <limits>
#include <cmath>
#include <vector>

#include "menu.h"

using namespace std;

Menu::Menu() : tabelaHash(1, MetodoDeColisao::ENCADEAMENTO), arvoreBJogos(64), arvoreBConquistas(64) {}

void Menu::menuInicial()
{
    inicializarTabelaHash();
    inicializarArvoreB();

    int opcao;
    do
    {
        cout << "\n=== Menu Inicial ===" << endl;
        cout << "1 - Inserir novo jogador" << endl;
        cout << "2 - Abrir o menu de consultas" << endl;
        cout << "3 - Exibir estatisticas da Hash" << endl;
        cout << "0 - Sair" << endl;
        cout << "Escolha: ";
        cin >> opcao;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "A opcao precisa ser numerica." << endl;
            continue;
        }

        switch (opcao)
        {
        case 1:
        {
            menuInsercaoHash();
            break;
        }
        case 2:
            menuDeConsultas();
            break;
        case 3:
            tabelaHash.exibirEstatisticas();
            break;
        case 0:
            cout << "Saindo...\n";
            break;
        default:
            cout << "Opcao invalida.\n";
        }

    } while (opcao != 0);
}

void Menu::menuDeConsultas()
{
    string entrada, id, minStr, maxStr, quantidadeTop;
    int opcao, min, max, quantidade;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    do
    {
        cout << "\n=== Menu Consultas ===\n";
        cout << "1 - Buscar jogador\n";
        cout << "2 - Listar jogos de um jogador\n";
        cout << "3 - Listar top N jogadores com mais jogos\n";
        cout << "4 - Listar top N jogadores com mais conquistas\n";
        cout << "5 - Mostrar jogadores entre um intervalo de conquistas\n";
        cout << "6 - Buscar jogadores que possuem determinado jogo\n";
        cout << "7 - Estatisticas do sistema\n";
        cout << "0 - Voltar\n";
        cout << "Escolha: ";
        getline(cin, entrada);

        try
        {
            opcao = stoi(entrada);
        }
        catch (...)
        {
            cout << "A opcao precisa ser numerica." << endl;
            continue;
        }

        switch (opcao)
        {
        case 1:
            menuBuscaHash();
            break;
        case 2:
            cout << "Digite o ID do jogador: ";
            getline(cin, id);
            {
                auto p = tabelaHash.busca(id);
                if (p)
                {
                    vector<shared_ptr<Jogo>> jogos = p->getJogos();
                    if (jogos.empty())
                    {
                        cout << "O jogador nao possui jogos cadastrados.\n";
                    }
                    else
                    {
                        cout << "Jogos do jogador " << id << ":\n";
                        for (const auto &jogo : jogos)
                        {
                            if (jogo) {
                                cout << "- " << jogo->getTitutlo() << " (ID: " << jogo->getId() << ")\n";
                            }
                        }
                    }
                }
                else
                {
                    cout << "Jogador nao encontrado.\n";
                }
            }
            break;
        case 3:
            cout << "Digite a quantidade do top a ser buscado: ";
            getline(cin, quantidadeTop);
            
            try
            {
                quantidade = stoi(quantidadeTop);
            }
            catch (...)
            {
                cout << "A quantidade do top precisa ser numericos." << endl;
                continue;
            }
            
            imprimeTopJogadores(quantidade);

            break;
        case 4:
            // adicionar aqui a função
            break;
        case 5:
            cout << "Digite o número mínimo de conquistas: ";
            getline(cin, minStr);
            cout << "Digite o número máximo de conquistas: ";
            getline(cin, maxStr);
            try
            {
                min = stoi(minStr);
                max = stoi(maxStr);
            }
            catch (...)
            {
                cout << "O minimo e maximo precisam ser numericos." << endl;
                continue;
            }
            // adicionar aqui a função
            break;
        case 6:
            cout << "Digite o id do jogo: ";
            getline(cin, id);
            // adicionar aqui a função
            break;
        case 7:
            // adicionar aqui a função
            break;
        case 0:
            cout << "Voltando...\n";
            break;
        default:
            cout << "Opcao invalida.\n";
        }

    } while (opcao != 0);
}

void Menu::inicializarTabelaHash()
{
    int metodoColisao;
    while (true)
    {
        cout << "Escolha o metodo de tratamento de colisao:\n";
        cout << "1 - Encadeamento (Chaining)\n";
        cout << "2 - Enderecamento Aberto (Sondagem Linear)\n";
        cout << "Opcao: ";
        cin >> metodoColisao;

        if (!cin.fail() && (metodoColisao == 1 || metodoColisao == 2))
            break;

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Opcao invalida. Digite 1 ou 2.\n";
    }

    cout << "Criando tabela hash...\n";

    MetodoDeColisao estrategia = (metodoColisao == 1) ? MetodoDeColisao::ENCADEAMENTO : MetodoDeColisao::SONDAGEM_LINEAR;

    HashPlayers geradorDePlayers;

    geradorDePlayers.populaTabelaComPlayers(this->tabelaHash, estrategia);
    cout << "Tabela criada e jogadores carregados!\n";
}

void Menu::inicializarArvoreB()
{
    cout << "Indexando jogadores por quantidade de jogos na Árvore B...\n";
    arvoreBJogos.indexarPorJogos(tabelaHash);

    cout << "Indexando jogadores por quantidade de conquistas na Árvore B...\n";
    arvoreBConquistas.indexarPorConquistas(tabelaHash);

    cout << "Árvore B inicializada com sucesso!\n";
}

void Menu::menuBuscaHash()
{
    string id;

    cout << "\n=== Buscar Jogador ===\n";
    cout << "Digite o ID do jogador: ";
    getline(cin, id);

    auto p = tabelaHash.busca(id); // agora é shared_ptr<Player>
    if (p)
    {
        cout << *p << endl;
    }
    else
    {
        cout << "Jogador nao encontrado.\n";
    }
}

void Menu::menuInsercaoHash()
{
    string id, pais;
    Utils utils;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "\n=== Inserir Jogador ===\n";

    while (true)
    {
        cout << "Digite o ID do jogador: (para voltar ao menu anterior, digite '0')";
        getline(cin, id);

        if (id == "0")
        {
            cout << "Voltando ao menu anterior...\n";
            return;
        }

        if (!utils.verificaIdJogador(id))
        {
            cout << "ID de jogador invalido! E preciso que ele tenha 17 digitos numericos.\n";
            continue;
        }

        if (tabelaHash.busca(id) != nullptr)
        {
            cout << "Jogador com este ID ja existe!\n";
            continue;
        }

        break;
    }

    cout << "Digite o pais: ";
    getline(cin, pais);

    auto novoJogador = make_shared<Player>(id, pais);
    //Player novoJogador(id, pais);

    tabelaHash.insere(novoJogador);
    cout << "Jogador inserido com sucesso!\n";
}

void Menu::imprimeTopJogadores(int quantidade){

    vector<shared_ptr<Player>> topJogadores = arvoreBJogos.buscaTopJogadores(quantidade);

    cout << "=== Top Jogadores ===\n";

    int i = 1;
    for (const auto &jogador : topJogadores)
    {
        if (jogador)
        {
            cout << "=== Top " << i << " ===" << endl;
            cout << jogador << endl;
        }
        i++;
    }

}