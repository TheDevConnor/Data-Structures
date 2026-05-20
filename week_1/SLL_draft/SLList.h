#ifndef SLLIST_H
#define SLLIST_H

#include "SLLNode.h"

template <typename T>
class SLList {
public:
    SLList();

    unsigned size() const; //return the size of the linked list
    bool empty() const; //return true if the list is empty and false otherwise

    void push_front(const T& value); //insert at the beginning of the list
    void push_back(const T& value); //insert at the end of the list
    void print() const; //print the content of the list

    /******************IMPLEMENT THIS*******/
    void pop_front();
    void pop_back();

private:
    SLLNode<T>* head; //the first node in the linked list
    SLLNode<T>* tail; //the last node in the linked list
    unsigned listSize; // the size of the list
};

#endif