#include <exception>
#include <iostream>

struct Node {
  int data;
  Node *next;

  Node(int d) : data(d), next(nullptr) {}
};

class Queue {
private:
  Node *front;
  Node *rear;

public:
  Queue() : front(nullptr), rear(nullptr) {}
  ~Queue() {
    while (front != nullptr) {
      deQueue();
    }
  }

  void enQueue(int x) {
    Node *new_node = new Node(x);

    if (this->rear == nullptr) {
      this->front = this->rear = new_node;
      return;
    }

    this->rear->next = new_node;
    this->rear = new_node;
  }

  void deQueue() {
    if (this->front == nullptr)
      return;

    Node *temp = this->front;
    this->front = this->front->next;

    if (this->front == nullptr)
      rear = nullptr;

    delete temp;
  }

  void printQueue() const {
    Node *fnode = this->front;
    std::cout << "Front: ";
    while (fnode != nullptr) {
        std::cout << fnode->data << " ";
        fnode = fnode->next;
    }
    std::cout << std::endl;
  }

  int getFront() const {
    if (front == nullptr) {
        throw std::string("Empty front queue");
    }
    return this->front->data;
  }

  int getRear() const {
    if (rear == nullptr) {
        throw std::string("Empty rear queue");
    }
    return this->rear->data;
  };
};

int main() {
  Queue q;
  q.enQueue(10);
  q.enQueue(20);
  q.deQueue();
  q.enQueue(30);
  q.enQueue(40);
  q.enQueue(50);
  q.deQueue();

  q.printQueue();

  try {
    std::cout << "Queue Front : " << q.getFront() << std::endl;
    std::cout << "Queue Rear : " << q.getRear() << std::endl;
  } catch (const std::exception &e) {
    std::cout << e.what() << std::endl;
  }

  return 0;
}