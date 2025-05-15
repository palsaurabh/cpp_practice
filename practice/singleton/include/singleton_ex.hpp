#include <iostream>
#include <string>
#include <mutex>
/**
 * Singleton design pattern:
 * The singleton design pattern is used when we need to control the number of instances of 
 * a particular class.
 * Here, the constructors for the class are hidden so that it can not be used to create objects
 * of that class. 
 * We create another method for creating the object if it doesnt exist or to return the same
 * object again if it already exists.
 * 
 * The instance created by the creator function is stored as a static member. The creator function
 * itself is declared static.
 *  */

/**
 * Create a singleton class
 */

 class Singleton 
 {
  private:
    std::string classname;
    Singleton(std::string name): classname{name}{};
    static Singleton *instance_;
    static std::mutex mutex_;
  public:
    Singleton(Singleton & obj) = delete;
    void operator=(const Singleton &obj) = delete;
    static Singleton * getInstance(const std::string &name);
    void printInstanceName();
 };
