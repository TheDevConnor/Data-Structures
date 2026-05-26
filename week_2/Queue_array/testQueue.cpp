#include "Queue.h"
#include "Queue.cpp"

#include <iostream>

int main() {
    Queue<int> q(4);
   
    try {
        q.enqueue(1);
        q.enqueue(2);
        q.enqueue(3);
        q.enqueue(4);
        q.enqueue(5); 
    }
    catch(std::string ex) {
        std::cout << ex << std::endl;
    }

    q.dequeue();
    q.dequeue();

    q.print();

    return 0;
}