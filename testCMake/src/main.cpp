// #include "functions/message.hpp"
#include "my_function/message.hpp"
#include <iostream>

int main() {
  std::cout << "hello cmake" << std::endl;
  Message say_hello("hello");
  std::cout << say_hello << std::endl;
  return 0;
}