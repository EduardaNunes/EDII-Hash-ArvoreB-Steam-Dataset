#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <iostream>

template <typename T>
struct Node
{
    T data;
    Node *next;
    Node(T d) : data(d), next(nullptr) {}
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
        Node<T> *current = head;
        while (current)
        {
            Node<T> *temp = current;
            current = current->next;
            delete temp;
        }
    }

    void insert(T data)
    {
        Node<T> *node = new Node<T>(data);
        node->next = head;
        head = node;
    }

    T *search(long long id) const
    {
        Node<T> *current = head;
        while (current)
        {
            if (current->data.getId() == id)
                return &current->data;
            current = current->next;
        }
        return nullptr;
    }

    bool isEmpty() const
    {
        return head == nullptr;
    }

    bool remove(long long id)
    {
        Node<T> *current = head;
        Node<T> *prev = nullptr;

        while (current)
        {
            if (current->data.getId() == id)
            {
                if (prev)
                    prev->next = current->next;
                else
                    head = current->next;

                delete current;
                return true;
            }
            prev = current;
            current = current->next;
        }
        return false;
    }
};

#endif
