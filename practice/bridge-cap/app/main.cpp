#include <iostream>
#include <string>
#include "bridge-cap_ex.hpp"
   
int main() {
  class Device *dev = new Radio();
  class Remote *simpleRmt = new simpleRemote(*dev);

  simpleRmt->incrementAudio();

  class Device *tv = new TV();
  class advRemote *adR = new advRemote(*tv);
  adR->incrementBrightness();

  class advRemote *adR1 = new advRemote(*dev);
  adR1->incrementBrightness();

  return 0;
}
