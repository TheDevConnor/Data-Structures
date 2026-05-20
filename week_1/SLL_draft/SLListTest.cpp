#include "SLList.h"
#include "SLList.cpp"

int main() {
    SLList<char> l;

    std::cout << "The size is " << l.size() << std::endl;
    std::cout << "Empty? " << l.empty() << std::endl;

    l.push_back('F');
    l.push_front('8');
    l.push_back('K');
    l.push_front('A');
    l.push_back('G');

    l.print();

    return 0;
}