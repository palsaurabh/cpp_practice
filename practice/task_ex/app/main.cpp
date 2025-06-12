#include <iostream>
#include <string>
#include <thread>
#include <future>

double divide(double a, double b) {
    std::this_thread::sleep_for(std::chrono::seconds(3));
    if (b == 0) {
        throw std::invalid_argument("Division by zero");
    }
    return a / b;
}

int main() {
    std::future<double> fut = std::async(divide, 10.0, 2.0);
    try{
        double result = fut.get();
        std::cout<<"result of division: "<<result<<"\n";
    }
    catch(const std::invalid_argument &e){
        std::cerr<<"Error: "<<e.what()<<"\n";
    }

    std::future<double> fut1 = std::async(std::launch::deferred, divide, 10.0, 0.0);
    try{
        double result = fut1.get();
        std::cout<<"result of division: "<<result<<"\n";
    }
    catch(const std::invalid_argument &e){
        std::cerr<<"Error: "<<e.what()<<"\n";
    }

    std::future<double> fut2 = std::async(divide, 10.0, 3.0);
    try{
        std::future_status result = fut2.wait_for(std::chrono::seconds(2));
        if(result == std::future_status::timeout)
        {
            std::cerr << "Operation timed out\n";
            return 1;
        }
        std::cout<<"result of division: "<<fut2.get()<<"\n";
    }
    catch(const std::invalid_argument &e){
        std::cerr<<"Error: "<<e.what()<<"\n";
    }

    return 0;
}
