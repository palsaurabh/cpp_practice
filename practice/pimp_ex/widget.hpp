// ----------------------
// interface (widget.hpp)
#include <experimental/propagate_const>
#include <iostream>
#include <memory>
 
class widget
{
    class impl;
    std::experimental::propagate_const<std::unique_ptr<impl>> pImpl;
public:
    void draw() const; // public API that will be forwarded to the implementation
    void draw();
    bool shown() const { return true; } // public API that implementation has to call
 
    widget(); // even the default ctor needs to be defined in the implementation file
              // Note: calling draw() on default constructed object is UB
    explicit widget(int);
    ~widget(); // defined in the implementation file, where impl is a complete type
    widget(widget&&); // defined in the implementation file
                      // Note: calling draw() on moved-from object is UB
    widget(const widget&) = delete;
    widget& operator=(widget&&); // defined in the implementation file
    widget& operator=(const widget&) = delete;
};
