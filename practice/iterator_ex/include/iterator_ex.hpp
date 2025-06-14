#include <iostream>
#include <string>
#include <vector>
/**
 *  */

template <typename T>
class Node {
public:
    T data;
    Node *left{nullptr}, *right{nullptr}, *parent{nullptr};
    Node(T data):data{data}{}
    Node(T data, Node *parent): data{data}, parent{parent}{}

    Node* addLeftChild(T data)
    {
        left = new Node(data, this);
        return this;
    }

    Node* addRightChild(T data)
    {
        right = new Node(data, this);
        return this;
    }

    void setParent(Node *parent)
    {
        this->parent = parent;
    }

    Node *getParent()
    {
        return parent;
    }

    template <typename U>
    friend std::ostream& operator<< (std::ostream& os, const Node<U>& obj);
    
    ~Node()
    {
        if(right)
            delete right;
        if(left)
            delete left;
        std::cout<<"Deleting Node! "<<data<<"\n";
    }
};

template <typename U>
std::ostream& operator<< (std::ostream& os, const Node<U>& obj)
{
    os << obj.data <<"\n";
    if(obj.left)
        os << *(obj.left) <<"\n";
    if(obj.right)
        os << *(obj.right) <<"\n";
    return os;
}


template<typename T>
class BinaryTreeC
{
public:
    Node<T> *rootNode{nullptr};
    BinaryTreeC(T data):rootNode{new Node<T>(data, nullptr)}{}
    
    template <typename U>
    friend std::ostream& operator<< (std::ostream& os, const BinaryTreeC<U>& obj);
    ~BinaryTreeC()
    {
        if(rootNode)
            delete rootNode;
    }
};

template <typename U>
std::ostream& operator<< (std::ostream& os, const BinaryTreeC<U>& obj)
{
    if(obj.rootNode)    
        os << *(obj.rootNode) <<"\n";
    return os;
}

