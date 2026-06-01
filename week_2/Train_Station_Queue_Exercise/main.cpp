#include <iostream>
#include <string>

struct Node {
  std::string name;
  Node *next;

  Node(std::string n) {
    name = n;
    next = nullptr;
  }
};

class Queue {
private:
  Node *front;
  Node *back;

public:
  Queue() {
    front = nullptr;
    back = nullptr;
  }

  bool empty() const { return front == nullptr; }

  // FUNCTION 1 TO IMPLEMENT
  void enqueue(std::string passenger) {
    Node *new_node = new Node(passenger);

    if (empty()) {
      front = new_node;
      back = new_node;
    } else {
      back->next = new_node;
      back = new_node;
    }
  }

  // FUNCTION 2 TO IMPLEMENT
  std::string dequeue() {
    if (empty())
      throw std::string("Queue is empty! Nobody to the board.");

    Node *temp = front;
    std::string r_name = front->name;

    front = front->next;
    delete temp;

    if (front == nullptr)
      back = nullptr;

    return r_name;
  }
};

int main() {
  Queue trainLine;

  trainLine.enqueue("Alice");
  trainLine.enqueue("Bob");
  trainLine.enqueue("Charlie");

  std::cout << trainLine.dequeue() << " boarded the train!" << std::endl;
  std::cout << trainLine.dequeue() << " boarded the train!" << std::endl;

  trainLine.enqueue("David");

  std::cout << trainLine.dequeue() << " boarded the train!" << std::endl;
  std::cout << trainLine.dequeue() << " boarded the train!" << std::endl;

  return 0;
}