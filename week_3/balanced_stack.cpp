#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#define MAX 100

  class Stack {
public:
  int top;
  char exp[MAX]; // Maximum size of Stack
  Stack() { top = -1; }
  bool push(char item);
  char pop();
};

bool Stack::push(char item) {
  if (top >= (MAX - 1)) {
    std::cout << "Stack Overflow";
    return false;
  } else {
    top++;
    exp[top] = item;
    return true;
  }
}

char Stack::pop() {
  if (top == -1) {
    std::cout << "stack underflow";
    return 0;
  } else {
    char x = exp[top];
    top--;
    return x;
  }
}

int isMatchingPair(char character1, char character2) {
  if (character1 == '(' && character2 == ')')
    return 1;
  else if (character1 == '{' && character2 == '}')
    return 1;
  else if (character1 == '[' && character2 == ']')
    return 1;
  else
    return 0;
}

int areParenthesisBalanced(char exp[]) {
  Stack s;
  int i = 0;

  while (exp[i] != '\0') {
    if (exp[i] == '{' || exp[i] == '(' || exp[i] == '[') {
        s.push(exp[i]);

        if (exp[i] == '}' || exp[i] == ')' || exp[i] == ']') {
            if (s.top == -1) 
                return 0;
            else if (!isMatchingPair(s.pop(), exp[i])) 
                return 0;
        }
    }
    i++;
  }

  return (s.top == -1) ? 1 : 0;
}

int main() {
  char exp[100];
  std::cout << "enter the expression:\n";
  std::cin >> exp;
  
  if (areParenthesisBalanced(exp))
    std::cout << "Balanced";
  else
    std::cout << "Not Balanced";
  return 0;
}