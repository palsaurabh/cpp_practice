#include <iostream>
#include "abstractfactory.hpp"

void concreteProduct1A::product_desc() const{
    std::cout<<"I am product 1 of family A\n";
}

void concreteProduct1B::product_desc() const{
    std::cout<<"I am product 1 of family B\n";
}

void concreteProduct2A::product_desc() const{
    std::cout<<"I am product 2 of family A\n";
}

void concreteProduct2B::product_desc() const {
    std::cout<<"I am product 2 of family B\n";
}

product1 *concreteProductFamilyA::createProduct1(){
    return new concreteProduct1A;
}

product2 *concreteProductFamilyA::createProduct2(){
    return new concreteProduct2A;
}

product1 *concreteProductFamilyB::createProduct1(){
    return new concreteProduct1B;
}

product2 *concreteProductFamilyB::createProduct2(){
    return new concreteProduct2B;
}

