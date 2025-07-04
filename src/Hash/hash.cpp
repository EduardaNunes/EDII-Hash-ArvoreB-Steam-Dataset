#include "hash.h"
#include "../LeitorDePlanilha/leitorDePlanilha.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <functional> // std::hash

using namespace std;

PlayerHashTable::PlayerHashTable(int size, CollisionMethod method)
    : tableSize(size), elementCount(0), collisionCount(0), collisionMethod(method),
      chainingTable(method == CollisionMethod::CHAINING ? size : 0),
      probingTable(method == CollisionMethod::LINEAR_PROBING ? size : 0) {}

int PlayerHashTable::computeHashIndex(const string& key) const {
    size_t hashValue = hash<string>{}(key);
    return static_cast<int>(hashValue % tableSize);
}

void PlayerHashTable::loadPlayersFromCSV(const string &filePath) {
    LeitorDePlanilha leitor;
    vector<vector<string>> dados = leitor.lerCSV(filePath);

    for (size_t i = 1; i < dados.size(); i++) {
        if (dados[i].size() >= 3) {
            string id = dados[i][0];
            string pais = dados[i][1];
            string dataCriacao = dados[i][2];

            if (!id.empty()) {
                insertPlayer(Player(id, pais, dataCriacao));
            }
        }
    }
}

void PlayerHashTable::insertPlayer(Player p) {
    int index = computeHashIndex(p.getId());

    if (collisionMethod == CollisionMethod::CHAINING) {
        Player *existing = chainingTable[index].busca(p.getId());
        if (existing) {
            *existing = p;
        } else {
            if (!chainingTable[index].eVazio())
                collisionCount++;

            chainingTable[index].insere(p);
            elementCount++;
            if ((float)elementCount / tableSize > 0.7f) {
                rehash();
            }
        }
    } else {
        int startIndex = index;
        int probeCount = 0;
        while (probingTable[index].state == EntryState::OCUPADO) {
            if (probingTable[index].data.getId() == p.getId()) {
                probingTable[index].data = p;
                return;
            }
            index = (index + 1) % tableSize;
            probeCount++;
            if (index == startIndex)
                return;
        }

        probingTable[index].data = p;
        probingTable[index].state = EntryState::OCUPADO;
        elementCount++;
        if ((float)elementCount / tableSize > 0.7f) {
            rehash();
        }

        if (probeCount > 0)
            collisionCount++;
    }
}

Player *PlayerHashTable::findPlayerById(const string& id) {
    int index = computeHashIndex(id);
    if (collisionMethod == CollisionMethod::CHAINING) {
        return chainingTable[index].busca(id);
    } else {
        int startIndex = index;
        while (probingTable[index].state != EntryState::VAZIO) {
            if (probingTable[index].state == EntryState::OCUPADO &&
                probingTable[index].data.getId() == id) {
                return &probingTable[index].data;
            }
            index = (index + 1) % tableSize;
            if (index == startIndex)
                break;
        }
        return nullptr;
    }
}

void PlayerHashTable::exibirEstatisticas() const {
    cout << "\n=== ESTATISTICAS ===" << endl;
    cout << "Tamanho da tabela: " << tableSize << endl;
    cout << "Elementos armazenados: " << elementCount << endl;
    cout << "Fator de carga: " << (float)elementCount / tableSize << endl;
    cout << "Numero de colisoes: " << collisionCount << endl;
}

void PlayerHashTable::rehash() {
    int newSize = nextPrime(tableSize * 2);

    if (collisionMethod == CollisionMethod::CHAINING) {
        vector<LinkedList<Player>> newTable(newSize);
        for (auto &list : chainingTable) {
            Node<Player> *current = list.getHead();
            while (current) {
                int newIndex = computeHashIndex(current->data.getId());
                newTable[newIndex].insere(current->data);
                current = current->proximo;
            }
        }
        chainingTable = move(newTable);
    } else {
        vector<HashEntry<Player>> newTable(newSize);
        for (auto &entry : probingTable) {
            if (entry.state == EntryState::OCUPADO) {
                int newIndex = computeHashIndex(entry.data.getId());
                while (newTable[newIndex].state == EntryState::OCUPADO) {
                    newIndex = (newIndex + 1) % newSize;
                }
                newTable[newIndex].data = entry.data;
                newTable[newIndex].state = EntryState::OCUPADO;
            }
        }
        probingTable = move(newTable);
    }

    tableSize = newSize;
    collisionCount = 0;
}

bool PlayerHashTable::isPrime(int number) {
    if (number <= 1) return false;
    if (number == 2) return true;
    if (number % 2 == 0) return false;
    for (int i = 3; i * i <= number; i += 2)
        if (number % i == 0)
            return false;
    return true;
}

int PlayerHashTable::nextPrime(int number) {
    while (!isPrime(number))
        number++;
    return number;
}
