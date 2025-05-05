// ---------------
// user (main.cpp)
#include "widget.hpp"
 
int main()
{
    widget w(7);
    const widget w2(8);
    w.draw();
    w2.draw();
}