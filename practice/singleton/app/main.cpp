#include <iostream>
#include <string>
#include "singleton_ex.hpp"
   
int main() {
  Singleton *instance = Singleton::getInstance("1");
  instance->printInstanceName();
  Singleton *instance1 = Singleton::getInstance("2");
  instance1->printInstanceName();
  return 0;
}
