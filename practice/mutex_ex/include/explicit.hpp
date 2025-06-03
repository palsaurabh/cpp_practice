#include <iostream>
#include <string>

class nonExplicit {
    public:
        int i_;
        // Constructor
        nonExplicit(int i) : i_(i) {}
};

int geti(const nonExplicit &ne)  
{ 
  return ne.i_; 
}

class explicitClass {
    public:
        int i_;
        // Constructor
        explicit explicitClass(int i) : i_(i) {}
};

int getie(const explicitClass &ne)  
{ 
  return ne.i_; 
}
