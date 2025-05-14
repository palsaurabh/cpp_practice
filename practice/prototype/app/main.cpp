#include <iostream>
#include <string>
#include "prototype_ex.hpp"
   
int main() {
  concretePrototype1 cp1(1,"1");
  cp1.printPrototype();
  Prototype *cp1copy = cp1.Clone();
  cp1copy->printPrototype();

  concretePrototype2 cp2(2,"2");
  cp2.printPrototype();
  Prototype *cp2copy = cp2.Clone();
  cp2copy->printPrototype();

  prototypeFactory pf;
  Prototype *cp1copy2 = pf.createPrototype("cp1");
  cp1copy2->printPrototype();
  return 0;
}
