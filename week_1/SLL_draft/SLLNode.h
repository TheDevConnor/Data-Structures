#ifndef SLLNODE_H
#define SLLNODE_H

#include <iostream>

template<typename T>
class SLLNode {
public:
    //T() - default template value
    SLLNode(const T& d = T(), SLLNode<T>* n = nullptr) {
        data = d;
        next = n;
    }

    T data;
    SLLNode<T>* next;
private:
};

#endif