#include <iostream>
#include <string>
#include <memory>
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
};

int main() {
    //Creating a unique pointer to my class
    std::unique_ptr<MyClass> myclassptr(new MyClass());
    //Creating a unique pointer to my class
    std::unique_ptr<MyClass> myclassptr2(new MyClass("MyClass2"));

    myclassptr2->printName();
    *myclassptr = *myclassptr2;
    myclassptr->printName();

    std::cout<<"Stack addresses: "<< myclassptr2.get() << " " << myclassptr.get() << "\n";
    myclassptr2.reset();
    std::cout<<"Stack addresses: "<< myclassptr2.get() << " " << myclassptr.get() << "\n";
    myclassptr2 = std::move(myclassptr);
    std::cout<<"Stack addresses: "<< myclassptr2.get() << " " << myclassptr.get() << "\n";
    

    std::shared_ptr<MyClass> sharemyclassptr(new MyClass("MyClass3"));
    std::shared_ptr<MyClass> sharemyclassptr2 = sharemyclassptr;
    sharemyclassptr->printName();
    std::cout<<"Stack address: "<< sharemyclassptr.get()<<"\n";
    std::cout<<"Use count: "<< sharemyclassptr.use_count()<<"\n";
    std::cout<<"Use count: "<< sharemyclassptr2.use_count()<<"\n";
    sharemyclassptr.reset();
    std::cout<<"Use count: "<< sharemyclassptr.use_count()<<"\n";

    sharemyclassptr2->printName();
    std::cout<<"Stack address: "<< sharemyclassptr2.get()<<"\n";
    std::cout<<"Use count: "<< sharemyclassptr2.use_count()<<"\n";

    return 0;
}
