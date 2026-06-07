#include <iostream>

void string_back(std::string s, int length) {
  if (length == 0)
    return;

  std::cout << s[length - 1];
  string_back(s, length - 1);
}

int pow(int base, int exp) {
  return ((exp == 0) 
          ? 1
          : (base * pow(base, exp - 1)));
}

// 1^1 + 2^2 + 3^3 + ... + n^n
int TotalSumToPower(int n, int p) {
  return ((n == 0) 
          ? 0
          : (pow(n, p) + TotalSumToPower(n-1, p-1)));
}

int main() {
  std::string s = "Hello World!";
  int length = s.length();

  string_back(s, length);
  std::cout << std::endl;

  int base = 2, exp = 3;
  std::cout << base << "^" << exp << " = " << pow(base, exp) << std::endl;

  int n = 5, p = 5;
  std::cout << "Total sum of " << n << "^" << p << " = " << TotalSumToPower(n, p) << std::endl;

  return 0;
}