#ifndef SLLIST_H
#define SLLIST_H

#include "SLLNode.h"

template <typename T>
class SLList {
public:
    SLList();

    unsigned size() const;
    bool empty() const;

    void push_front(const T& value);
    void push_back(const T& value);
    void print() const;

    void pop_front();
    void pop_back();

private:
    SLLNode<T>* head;
    SLLNode<T>* tail;
    unsigned listSize;
};

#endif