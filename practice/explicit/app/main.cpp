#include <iostream>
#include <string>
#include "explicit.hpp"
   
int main() {
  nonExplicit n(10.0);
  nonExplicit n2 = 10.0; // This will not cause a compilation error
  std::cout << "nonExplicit: " << geti(n) << std::endl;  
  std::cout << "nonExplicit: " << geti(n2) << std::endl; //Compilation Error
  explicitClass e(10.0);  
  // std::cout << "explicitClass: " << getie(10) << std::endl; //Compilation Error
  // explicitClass e2 = 10.0; // This will cause a compilation error
  return 0;
}
