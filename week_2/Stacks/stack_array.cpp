#include <iostream>

#define MAX 100
class Stack {
  int top;

public:
  int a[MAX];
  Stack() { top = -1; }
  bool push(int item);
  int pop();
  int peek();
  bool isEmpty();
};

bool Stack::push(int item) {
  if (top >= MAX - 1)
    throw std::string("Stack overflow\n");
  a[++top] = item;
  return true;
}

int Stack::pop() {
  if (top < 0)
    throw std::string("Stack underflow\n");
  return a[top--];
}

int Stack::peek() {
  if (top < 0)
    throw std::string("Stack is empty");
  return a[top];
}

bool Stack::isEmpty() { return (top < 0); }

int main() {
  class Stack s;
  s.push(4);
  s.push(5);
  s.push(6);

  std::cout << s.pop() << " is successfully popped from stack\n";
  std::cout << "Elements present in stack : ";

  while (!s.isEmpty()) {
    std::cout << s.pop() << " ";
  }

  return 0;
}