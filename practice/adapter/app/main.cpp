#include <iostream>
#include <string>
#include "adapter_ex.hpp"
   
int main() {
  Hole hole(5);
  roundPeg rp(4);
  std::cout<<"Round peg fits? "<<hole.fits(rp)<<"\n";
  squarePeg sqPeg(10);
  squarePegAdapter sa(sqPeg);
  std::cout<<"Square Peg fits? "<<hole.fits(sa)<<"\n";
  return 0;
}
