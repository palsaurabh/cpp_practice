#include <iostream>
#include <string>

#include "singleton_ex.hpp"
/**
 * Singleton design pattern:
 * Thread-unsafe version
 * */

  Singleton *Singleton::instance_{nullptr};
  std::mutex Singleton::mutex_;
  Singleton * Singleton::getInstance(const std::string &name)
  {
    std::lock_guard<std::mutex> lock(mutex_);
    if (instance_ == nullptr)
      instance_ = new Singleton(name);

    return instance_;
  }

  void Singleton::printInstanceName()
  {
    std::cout<<"Instance name: "<<classname<<"\n";
  }
