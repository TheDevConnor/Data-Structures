#include <iostream>

struct Node {
  int data;
  Node *next;
};

class Stack {
private:
  Node *top;

public:
  Stack() : top(nullptr) {}
  ~Stack() {
    while (!isEmpty()) {
      pop();
    }
  }
  bool isEmpty() { return top == nullptr; }

  void push(int data) {
    Node *temp = new Node();
    temp->data = data;
    temp->next = top;
    top = temp;
  }
  
  int peek() { 
    if (top == nullptr) 
        throw std::string("Stack is Empty!"); 
    return top->data;
  }
  
  void pop() {
    if (top == nullptr)
        throw std::string("Stack Underflow!");

    Node *temp = top;
    top = top->next;
    delete temp;
  }
  
  void printList() {
    if (isEmpty()) {
      std::cout << "\nStack is empty";
      return;
    }
    Node *temp = top;
    while (temp != nullptr) {
      std::cout << temp->data << " -> ";
      temp = temp->next;
    }
    std::cout << "NULL" << std::endl;
  }
};

int main() {
  Stack s;
  s.push(11);
  s.push(22);
  s.push(33);
  s.push(44);
  s.printList();
  std::cout << "\nTop element is " << s.peek() << std::endl;
  s.pop();
  s.pop();
  s.printList();
  std::cout << "\nTop element is " << s.peek() << std::endl;
  return 0;
}