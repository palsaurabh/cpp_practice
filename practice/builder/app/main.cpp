#include <iostream>
#include <string>
#include "builder_ex.hpp"
   
int main() {
  palaceBuilder Builder;
  shelterMakingDirector *Director = new shelterMakingDirector(Builder);
  Director->createLargeShelter();
  Palace *palace = Builder.getProduct();
  std::cout<<palace->listShelterDetails();
  delete palace;
  return 0;
}
