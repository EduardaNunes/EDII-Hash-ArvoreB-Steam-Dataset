#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <vector>
#include <stdexcept>
#include <iostream>
#include "linked_list.h"
#include "hash_entry.h"

using namespace std;

enum class MetodoDeColisao {
    ENCADEAMENTO,
    SONDAGEM_LINEAR
};

// --------------------- DECLARAÇÃO ----------------------

template<typename T>
class TabelaHash {
private:
    int tamanho;
    int numeroDeElementos;
    int numeroDeColisoes;
    MetodoDeColisao metodoDeColisao;

    vector<LinkedList<T>> encadeamento;
    vector<HashEntry<T>> sondagemLinear;

    int calculaIndexDaHash(long long chave) const;
    bool ePrimo(int n);
    int proximoPrimo(int n);
    void rehash();

public:
    TabelaHash(int size, MetodoDeColisao metodo);

    void insere(const T& obj);
    T* busca(long long id);
    bool remove(long long id);
    void exibirEstatisticas() const;
};

// -------------------- IMPLEMENTAÇÃO ---------------------

template<typename T>
TabelaHash<T>::TabelaHash(int size, MetodoDeColisao metodo)
    : tamanho(size), numeroDeElementos(0), numeroDeColisoes(0), metodoDeColisao(metodo),
      encadeamento(metodo == MetodoDeColisao::ENCADEAMENTO ? size : 0),
      sondagemLinear(metodo == MetodoDeColisao::SONDAGEM_LINEAR ? size : 0) {}

template<typename T>
int TabelaHash<T>::calculaIndexDaHash(long long chave) const {
    if (chave < 0) throw invalid_argument("Chave negativa não permitida.");
    return chave % tamanho;
}

template<typename T>
bool TabelaHash<T>::ePrimo(int n) {
    if (n <= 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    for (int i = 3; i * i <= n; i += 2)
        if (n % i == 0) return false;
    return true;
}

template<typename T>
int TabelaHash<T>::proximoPrimo(int n) {
    while (!ePrimo(n)) n++;
    return n;
}

template<typename T>
void TabelaHash<T>::rehash() {
    int novoTamanho = proximoPrimo(tamanho * 2);
    if (metodoDeColisao == MetodoDeColisao::ENCADEAMENTO) {
        vector<LinkedList<T>> novaTabela(novoTamanho);
        for (auto &list : encadeamento) {
            Node<T> *atual = list.getHead();
            while (atual) {
                int novoIndex = atual->data.getId() % novoTamanho;
                novaTabela[novoIndex].insere(atual->data);
                atual = atual->next;
            }
        }
        encadeamento = move(novaTabela);
    } else {
        vector<HashEntry<T>> novaTabela(novoTamanho);
        for (auto &entry : sondagemLinear) {
            if (entry.state == EntryState::OCUPADO) {
                int novoIndex = entry.data.getId() % novoTamanho;
                while (novaTabela[novoIndex].state == EntryState::OCUPADO)
                    novoIndex = (novoIndex + 1) % novoTamanho;

                novaTabela[novoIndex].data = entry.data;
                novaTabela[novoIndex].state = EntryState::OCUPADO;
            }
        }
        sondagemLinear = move(novaTabela);
    }

    tamanho = novoTamanho;
    numeroDeColisoes = 0;
}

template<typename T>
void TabelaHash<T>::insere(const T& obj) {
    int index = calculaIndexDaHash(obj.getId());

    if (metodoDeColisao == MetodoDeColisao::ENCADEAMENTO) {
        T* existe = encadeamento[index].search(obj.getId());
        if (existe) {
            *existe = obj;
        } else {
            if (!encadeamento[index].eVazio())
                numeroDeColisoes++;

            encadeamento[index].insere(obj);
            numeroDeElementos++;
            if ((float)numeroDeElementos / tamanho > 0.7f)
                rehash();
        }
    } else {
        int indexInicial = index;
        int contador = 0;
        while (sondagemLinear[index].state == EntryState::OCUPADO) {
            if (sondagemLinear[index].data.getId() == obj.getId()) {
                sondagemLinear[index].data = obj;
                return;
            }
            index = (index + 1) % tamanho;
            contador++;
            if (index == indexInicial)
                return;
        }

        sondagemLinear[index].data = obj;
        sondagemLinear[index].state = EntryState::OCUPADO;
        numeroDeElementos++;
        if ((float)numeroDeElementos / tamanho > 0.7f)
            rehash();

        if (contador > 0)
            numeroDeColisoes++;
    }
}

template<typename T>
T* TabelaHash<T>::busca(long long id) {
    int index = calculaIndexDaHash(id);

    if (metodoDeColisao == MetodoDeColisao::ENCADEAMENTO) {
        return encadeamento[index].search(id);
    } else {
        int indexInicial = index;
        while (sondagemLinear[index].state != EntryState::VAZIO) {
            if (sondagemLinear[index].state == EntryState::OCUPADO &&
                sondagemLinear[index].data.getId() == id)
                return &sondagemLinear[index].data;

            index = (index + 1) % tamanho;
            if (index == indexInicial)
                break;
        }
        return nullptr;
    }
}

template<typename T>
bool TabelaHash<T>::remove(long long id) {
    int index = calculaIndexDaHash(id);

    if (metodoDeColisao == MetodoDeColisao::ENCADEAMENTO) {
        if (encadeamento[index].remove(id)) {
            numeroDeElementos--;
            return true;
        }
    } else {
        int indexInicial = index;
        while (sondagemLinear[index].state != EntryState::VAZIO) {
            if (sondagemLinear[index].state == EntryState::OCUPADO &&
                sondagemLinear[index].data.getId() == id) {
                sondagemLinear[index].state = EntryState::REMOVIDO;
                numeroDeElementos--;
                return true;
            }
            index = (index + 1) % tamanho;
            if (index == indexInicial)
                break;
        }
    }

    return false;
}

template<typename T>
void TabelaHash<T>::exibirEstatisticas() const {
    cout << "Tamanho da Tabela: " << tamanho << endl;
    cout << "Elementos: " << numeroDeElementos << endl;
    cout << "Colisões: " << numeroDeColisoes << endl;
    cout << "Fator de Carga: " << (float)numeroDeElementos / tamanho << endl;
}

#endif
