#ifndef SLLNODE_H
#define SLLNODE_H

#include <iostream>

template<typename T>
class SLLNode {
public:
    SLLNode(const T& d = T(), SLLNode<T>* n = nullptr) {
        data = d;
        next = n;
    }

    T data;
    SLLNode<T>* next;
};

#endif