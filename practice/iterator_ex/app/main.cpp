#include <iostream>
#include <string>
#include "iterator_ex.hpp"
   
int main() {
    BinaryTreeC<std::string> bt("rootNode");
    bt.rootNode->addLeftChild("1L")->addRightChild("1R")->right->addLeftChild("1RL")->addRightChild("1RR")->parent->left->addLeftChild("1LL")->addRightChild("1LR");
    std::cout<<bt;
    return 0;
}
