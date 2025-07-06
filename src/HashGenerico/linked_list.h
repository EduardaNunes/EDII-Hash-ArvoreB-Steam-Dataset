#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <iostream>
#include <string>
#include <memory>

// template para o nó da lista encadeada
template <typename T>
struct Node
{
    T data;
    Node *proximo;
    Node(T d) : data(d), proximo(nullptr) {}
};

// Classe LinkedList que implementa uma lista encadeada genérica
template <typename T>
class LinkedList
{
private:
    Node<T> *head;

public:
    LinkedList() : head(nullptr) {}

    Node<T> *getHead() const
    {
        return head;
    }

    ~LinkedList()
    {
        Node<T> *atual = head;
        while (atual)
        {
            Node<T> *temp = atual;
            atual = atual->proximo;
            delete temp;
        }
    }

    // Insere um novo nó no início da lista
    void insere(T data)
    {
        Node<T> *node = new Node<T>(data);
        node->proximo = head;
        head = node;
    }

    // Busca um nó na lista pelo ID
    T busca(const std::string &id) const
    {
        Node<T> *atual = head;
        while (atual)
        {
            if (atual->data->getId() == id)
                return atual->data;
            atual = atual->proximo;
        }
        return nullptr;
    }

    // Verifica se a lista está vazia
    bool eVazio() const
    {
        return head == nullptr;
    }

    // realiza uma operação para cada elemento da lista
    template <typename Func>
    void forEach(Func func) const
    {
        Node<T> *atual = head;
        while (atual)
        {
            func(atual->data);
            atual = atual->proximo;
        }
    }
};

#endif
