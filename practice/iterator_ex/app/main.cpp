#include <iostream>
#include <string>
#include "iterator_ex.hpp"
#include <chrono>   
#include<thread>
int main() {
    BinaryTreeC<std::string> bt("rootNode");
    Node<std::string> *intmdt_node = bt.rootNode->addLeftChild("1L")->addRightChild("1R")->left->addLeftChild("1LL")->addRightChild("1LR")->parent->right->addLeftChild("1RL")->addRightChild("1RR")->right->addRightChild("2RRR")->right->addRightChild("3RRRR");
    intmdt_node->addLeftChild("3LL")->left->addLeftChild("4LLL")->left->addLeftChild("5LLLLL")->addRightChild("6RRRRRR");
    std::cout<<bt;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    for(auto it = bt.begin(); it != bt.end(); ++it)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        if(!(*it).data.empty())
        {
            std::cout<<(*it).data<<'\n';
        }
    }
    return 0;
}
