#include <iostream>
#include <string>
#include <thread>
#include <future>
#include <mutex>
#include <vector>

class nonExplicit {
  public:
      int i_;
      // Constructor
      nonExplicit(int i) : i_(i) {}

      void modify_i()
      {
        std::lock_guard<std::mutex> lock(mtx);
        std::cout<<"i_="<<i_<<"\n";
        i_++;
      }
      std::mutex mtx;
};

int main() {
  nonExplicit ne(1);
  std::future<void> fut = std::async(&nonExplicit::modify_i, &ne);

  std::vector<std::future<void>> futs;
  for (int i = 0; i < 1000; i++)
  {
    std::future<void> lfut = std::async(&nonExplicit::modify_i, &ne);
    futs.emplace_back(std::move(lfut));
  }

  for(auto &&f : futs)
  {
    f.wait();    
  }
  fut.wait();
  return 0;
}
