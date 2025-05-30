#include <iostream>
#include <string>
#include <thread>
#include <future>   
class nonExplicit {
    public:
        int i_;
        // Constructor
        nonExplicit(int i) : i_(i) {}
};


int main() {
  std::promise<nonExplicit> prom;
  std::future<nonExplicit> fut = prom.get_future();

  auto lamb = [&prom]()
  {
    nonExplicit ne(1);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    prom.set_value(std::move(ne));
  };
  std::thread promise_thread((lamb));
  std::cout<<"Wating for future\n";
  nonExplicit ne1 = fut.get();
  std::cout<<"got future "<< ne1.i_<<"\n";
  promise_thread.join();
  return 0;
}
