#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>

std::string postfixTokens[200];
int postfixSize = 0;

template <typename T> struct Stack {
  T data[200];
  int top = -1;

  void push(T val) { data[++top] = val; }
  T pop() { return data[top--]; }
  T peek() { return data[top]; }
  bool isEmpty() { return top == -1; }
};

bool isOperator(char c) {
  return c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '^';
}

bool isOpenParen(char c) { return c == '(' || c == '{' || c == '['; }
bool isCloseParen(char c) { return c == ')' || c == '}' || c == ']'; }

bool matchesParen(char open, char close) {
  return (open == '(' && close == ')') || (open == '{' && close == '}') ||
         (open == '[' && close == ']');
}

int precedence(char op) {
  switch (op) {
  case '+':
  case '-':
    return 1;
  case '*':
  case '/':
  case '%':
    return 2;
  case '^':
    return 3;
  default:
    return 0;
  }
}

bool isRightAssoc(char op) { return op == '^'; }

std::string preprocess(const std::string &input) {
  std::string result;
  for (char c : input) {
    if (c == ' ')
      continue;

    if (!isdigit(c) && !isOperator(c) && !isOpenParen(c) && !isCloseParen(c)) {
      std::cout << "Error: Invalid character '" << c << "' in expression"
                << std::endl;
      return "";
    }
    result += c;
  }
  return result;
}

void emitOperator(char op, Stack<char> &ops, std::string &output) {
  while (!ops.isEmpty() && isOperator(ops.peek()) &&
         (precedence(ops.peek()) > precedence(op) ||
          (precedence(ops.peek()) == precedence(op) && !isRightAssoc(op)))) {
    char top = ops.pop();
    postfixTokens[postfixSize++] = std::string(1, top);
    output += top;
  }
  ops.push(op);
}

void emitNumber(const std::string &expr, int &i, std::string &output) {
  std::string num;
  while (i < (int)expr.size() && isdigit(expr[i]))
    num += expr[i++];
  postfixTokens[postfixSize++] = num;
  output += num;
}

bool emitCloseParen(char close, Stack<char> &ops, std::string &output) {
  while (!ops.isEmpty() && !isOpenParen(ops.peek())) {
    char op = ops.pop();
    postfixTokens[postfixSize++] = std::string(1, op);
    output += op;
  }
  if (ops.isEmpty() || !matchesParen(ops.pop(), close)) {
    std::cout << "Error: Mismatched parentheses" << std::endl;
    return false;
  }
  return true;
}

bool applyOperator(char op, Stack<double> &vals) {
  if (vals.top < 1) {
    std::cout << "Error: Invalid expression (too few operands)" << std::endl;
    return false;
  }
  double b = vals.pop();
  double a = vals.pop();

  switch (op) {
  case '+':
    vals.push(a + b);
    break;
  case '-':
    vals.push(a - b);
    break;
  case '*':
    vals.push(a * b);
    break;
  case '%':
    vals.push(fmod(a, b));
    break;
  case '^':
    vals.push(pow(a, b));
    break;
  case '/':
    if (b == 0) {
      std::cout << "Error: Division by zero" << std::endl;
      return false;
    }
    vals.push(a / b);
    break;
  }
  return true;
}

std::string to_postfix(const std::string &infix) {
  std::string expr = preprocess(infix);
  if (expr.empty())
    return "";

  postfixSize = 0;
  Stack<char> ops;
  std::string output;

  for (int i = 0; i < (int)expr.size();) {
    char c = expr[i];

    if (isdigit(c)) {
      emitNumber(expr, i, output);
      continue;
    } else if (isOpenParen(c))
      ops.push(c);
    else if (isCloseParen(c)) {
      if (!emitCloseParen(c, ops, output))
        return "";
    } else if (isOperator(c))
      emitOperator(c, ops, output);

    i++;
  }

  while (!ops.isEmpty()) {
    char op = ops.pop();
    if (isOpenParen(op)) {
      std::cout << "Error: Mismatched parentheses" << std::endl;
      return "";
    }
    postfixTokens[postfixSize++] = std::string(1, op);
    output += op;
  }

  return output;
}

void print_postfix(const std::string &postfix) {
  if (!postfix.empty())
    std::cout << "Postfix expression: " << postfix << std::endl;
}

double evaluatePostfix(const std::string &postfix) {
  if (postfix.empty())
    return 0;

  Stack<double> vals;

  for (int i = 0; i < postfixSize; i++) {
    const std::string &tok = postfixTokens[i];
    bool isOp = tok.size() == 1 && isOperator(tok[0]);

    if (isOp && !applyOperator(tok[0], vals))
      return 0;
    if (!isOp)
      vals.push(std::stod(tok));
  }

  if (vals.top != 0) {
    std::cout << "Error: Invalid expression (too many operands)" << std::endl;
    return 0;
  }

  double result = vals.pop();
  std::cout << "Result: " << std::fixed << std::setprecision(3) << result
            << std::endl;
  return result;
}

int main() {
  std::string infixExpression;
  std::cout << "Enter an infix expression: ";
  getline(std::cin, infixExpression);

  std::string postfixExp = to_postfix(infixExpression);
  print_postfix(postfixExp);
  double result = evaluatePostfix(postfixExp);

  return 0;
}