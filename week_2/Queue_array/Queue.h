#ifndef QUEUE_H
#define QUEUE_H

#include <string>

template<typename T>
class Queue {
public:
    Queue(unsigned capacity = 10);
    
    unsigned size() const;
    bool empty() const;
    bool full() const;

    const T& front() const;

    void enqueue(const T& val);
    void dequeue();

    void print() const;

private:
    T* data;
    unsigned queueSize;
    unsigned capacity;
    int frnt;
    int bck;
};

#endif