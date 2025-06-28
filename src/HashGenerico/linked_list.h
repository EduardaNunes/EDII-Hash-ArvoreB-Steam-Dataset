#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <iostream>

template <typename T>
struct Node
{
    T data;
    Node *proximo;
    Node(T d) : data(d), proximo(nullptr) {}
};

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

    void insere(T data)
    {
        Node<T> *node = new Node<T>(data);
        node->proximo = head;
        head = node;
    }

    T *busca(long long id) const
    {
        Node<T> *atual = head;
        while (atual)
        {
            if (atual->data.getId() == id)
                return &atual->data;
            atual = atual->proximo;
        }
        return nullptr;
    }

    bool eVazio() const
    {
        return head == nullptr;
    }

    bool remove(long long id)
    {
        Node<T> *atual = head;
        Node<T> *prev = nullptr;

        while (atual)
        {
            if (atual->data.getId() == id)
            {
                if (prev)
                    prev->proximo = atual->proximo;
                else
                    head = atual->proximo;

                delete atual;
                return true;
            }
            prev = atual;
            atual = atual->proximo;
        }
        return false;
    }
};

#endif
