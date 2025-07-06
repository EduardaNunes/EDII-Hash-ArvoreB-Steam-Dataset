#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <vector>
#include <stdexcept>
#include <iostream>
#include <string>
#include <functional>  
#include <memory>
#include "linked_list.h"
#include "hash_entry.h"

using namespace std;

enum class MetodoDeColisao {
    ENCADEAMENTO,
    SONDAGEM_LINEAR
};

template<typename T>
class TabelaHash {
private:
    int tamanho;
    int numeroDeElementos;
    int numeroDeColisoes;
    MetodoDeColisao metodoDeColisao;

    vector<LinkedList<shared_ptr<T>>> encadeamento;
    vector<HashEntry<shared_ptr<T>>> sondagemLinear;

    int calculaIndexDaHash(const string& chave) const;
    bool ePrimo(int n);
    int proximoPrimo(int n);
    void rehash();

public:
    TabelaHash(int tam, MetodoDeColisao metodo);

    void insere(const shared_ptr<T>& obj);
    shared_ptr<T> busca(const string& id);
    void exibirEstatisticas() const;
};

template<typename T>
TabelaHash<T>::TabelaHash(int tam, MetodoDeColisao metodo)
    : tamanho(tam), numeroDeElementos(0), numeroDeColisoes(0), metodoDeColisao(metodo),
      encadeamento(metodo == MetodoDeColisao::ENCADEAMENTO ? tam : 0),
      sondagemLinear(metodo == MetodoDeColisao::SONDAGEM_LINEAR ? tam : 0) {}

template<typename T>
int TabelaHash<T>::calculaIndexDaHash(const string& chave) const {
    size_t valorHash = hash<string>{}(chave);
    return static_cast<int>(valorHash % tamanho);
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
    tamanho = novoTamanho;
    if (metodoDeColisao == MetodoDeColisao::ENCADEAMENTO) {
        vector<LinkedList<shared_ptr<T>>> novaTabela(novoTamanho);
        for (auto &list : encadeamento) {
            Node<shared_ptr<T>> *atual = list.getHead();
            while (atual) {
                int novoIndex = calculaIndexDaHash(atual->data->getId());
                novaTabela[novoIndex].insere(atual->data);
                atual = atual->proximo;
            }
        }
        encadeamento = move(novaTabela);
    } else {
        vector<HashEntry<shared_ptr<T>>> novaTabela(novoTamanho);
        for (auto &entry : sondagemLinear) {
            if (entry.state == EntryState::OCUPADO) {
                int novoIndex = calculaIndexDaHash(entry.data->getId());
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
void TabelaHash<T>::insere(const shared_ptr<T>& obj) {
    int index = calculaIndexDaHash(obj->getId());

    if (metodoDeColisao == MetodoDeColisao::ENCADEAMENTO) {
        shared_ptr<T> existe = encadeamento[index].busca(obj->getId());
        if (existe) {
            existe = obj; // sobrescreve o ponteiro armazenado
            return;
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
            if (sondagemLinear[index].data->getId() == obj->getId()) {
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
shared_ptr<T> TabelaHash<T>::busca(const string& id) {
    int index = calculaIndexDaHash(id);

    if (metodoDeColisao == MetodoDeColisao::ENCADEAMENTO) {
        return encadeamento[index].busca(id);
    } else {
        int indexInicial = index;
        while (sondagemLinear[index].state != EntryState::VAZIO) {
            if (sondagemLinear[index].state == EntryState::OCUPADO &&
                sondagemLinear[index].data->getId() == id)
                return sondagemLinear[index].data;

            index = (index + 1) % tamanho;
            if (index == indexInicial)
                break;
        }
        return nullptr;
    }
}

template<typename T>
void TabelaHash<T>::exibirEstatisticas() const {
    cout << "Tamanho da Tabela: " << tamanho << endl;
    cout << "Elementos: " << numeroDeElementos << endl;
    cout << "Colisoes: " << numeroDeColisoes << endl;
    cout << "Fator de Carga: " << (float)numeroDeElementos / tamanho << endl;
}

#endif