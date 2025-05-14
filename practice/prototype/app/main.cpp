#include <iostream>
#include <string>
#include "prototype_ex.hpp"
   
int main() {
  concretePrototype cp1(1,2);
  cp1.printPrototype();
  Prototype *cp2 = cp1.Clone();
  cp2->printPrototype();
  return 0;
}
