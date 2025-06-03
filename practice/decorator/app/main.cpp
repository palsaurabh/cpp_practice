#include <iostream>
#include <string>
#include "decorator_ex.hpp"
   
int main() {
  BasicNotifier bn; 
  FacebookNotifier *fbn = new FacebookNotifier(&bn);
  WhatsappNotifier *wan = new WhatsappNotifier(fbn);

  wan->notify();
  return 0;
}
