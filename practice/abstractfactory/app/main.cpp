#include <iostream>
#include "abstractfactory.hpp"

void client_code(productFamily *pf){
    pf->list_products();
}

int main()
{
    concreteProductFamilyA cpfA;
    client_code(&cpfA);
    concreteProductFamilyB cpfB;
    client_code(&cpfB);

    return 0;

}