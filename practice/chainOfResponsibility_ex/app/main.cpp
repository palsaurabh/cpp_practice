#include <iostream>
#include <string>
#include "chainOfResponsibility_ex.hpp"
   
int main() {
  IHandler *hndl = new CatHandler();
  hndl->setNext(new DogHandler())->setNext(new HorseHandler())->setNext(nullptr);

  hndl->handle("Neigh");
  hndl->handle("Deigh");
  hndl->handle("Meow");
  return 0;
}
