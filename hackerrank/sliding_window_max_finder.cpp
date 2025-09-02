/*
Given a set of arrays of size  and an integer , you have to find the maximum integer for each and every contiguous subarray of size  for each of the given arrays.

Input Format

First line of input will contain the number of test cases T. For each test case, you will be given the size of array N and the size of subarray to be used K. This will be followed by the elements of the array Ai.

Constraints



 , where  is the  element in the array .

Output Format

For each of the contiguous subarrays of size  of each array, you have to print the maximum integer.

Sample Input

2
5 2
3 4 6 3 4
7 4
3 4 5 8 1 4 10*/
#include <iostream>
#include <vector>
#include <deque>
#include <sstream>
#include <algorithm>
#include <limits>

// void sliding_window_max_finder(const int count, const int k, const std::string& input) {
//     std::deque<int> dq;   // stores indices
//     std::stringstream ss{input};
//     std::vector<int> arr(count);
//     for (int i = 0; i < count; i++) ss >> arr[i];

//     for (int i = 0; i < count; i++) {
//         // Remove indices out of this window
//         if (!dq.empty() && dq.front() <= i - k)
//             dq.pop_front();

//         // Remove smaller values (not useful anymore)
//         while (!dq.empty() && arr[dq.back()] <= arr[i])
//             dq.pop_back();

//         dq.push_back(i);

//         // Window has formed, print max
//         if (i >= k - 1)
//             std::cout << arr[dq.front()] << " ";
//     }
//     std::cout << "\n";
// }
void sliding_window_max_finder(const int count, const int sliding_window_size, const std::string& input){
    std::deque<int> deq;
    std::stringstream ss{input};
    for(int i = 0; i < count; i++){
        int val;
        ss >> val;
        deq.push_back(val);
        if(deq.size() == sliding_window_size){
            auto it = std::max_element(deq.begin(), deq.end());
            std::cout<<*it<<' ';        
            deq.pop_front();
        }
    }  
    std::cout<<"\n";
}

int main(){
    int numTestcases;
    std::cin>>numTestcases;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::vector<std::string> input;
    for(int i = 1; i <= numTestcases*2; i++){
        std::string line;
        std::getline(std::cin, line);
        input.emplace_back(line);
    }
    for(int i = 0; i < numTestcases*2; i++){
        int count, sliding_window_size;
        std::stringstream ss(input[i++]);
        ss >> count >> sliding_window_size;
        sliding_window_max_finder(count, sliding_window_size, input[i]);
    }
}