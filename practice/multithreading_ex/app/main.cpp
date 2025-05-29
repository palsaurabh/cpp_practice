#include <iostream>
#include <string>
#include <thread>
// #include "uniquePtr_ex.hpp"

class MyClass {
  private:
    std::string name;
  public:
    MyClass() {
        std::cout << "MyClass constructor\n";
    }
    MyClass(const std::string& name) : name(name) {
        std::cout << "MyClass constructor\n";
    }
    ~MyClass() {
        std::cout<<"MyClass Destructor\n";
    }
    void printName() {
        std::cout << "MyClass name: " << name << "\n";
    }

    void operator()(){
        std::cout<<"MyClass opeartor() called\n";
    }
};

void func(void)
{
    std::cout << "Function called\n";
}

void func2(int i)
{
    std::cout << "Function called with argument: " << i << "\n";
}

int main() {
    std::thread t1(func);
    std::thread t2(func2, 2);

    auto functor1 = [](){
        std::cout<<"My Lambda called\n";
    };
    std::thread t3(functor1);
    std::thread t4{MyClass()};
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    return 0;
}
