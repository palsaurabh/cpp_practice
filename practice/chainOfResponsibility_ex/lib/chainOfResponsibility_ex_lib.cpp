#include <iostream>
#include <string>
#include <cmath>
#include "chainOfResponsibility_ex.hpp"
/*Abstract Handler implements a basic or default functionality*/

void AbstractHandler::handle(std::string str)
{
    if (this->nexthandler != nullptr)
        this->nexthandler->handle(str);
    else
        std::cout<<"Can't Handle\n";
}

IHandler *AbstractHandler::setNext(IHandler *nxthandler)
{
    nexthandler = nxthandler;
    return nexthandler;
}

void DogHandler::handle(std::string str)
{
    if(str == "Bow")
    {
        std::cout<<str<<" "<<str<<'\n';
    }
    else
    {
        AbstractHandler::handle(str);
    }
}

void HorseHandler::handle(std::string str)
{
    if(str == "Neigh")
    {
        std::cout<<str<<" "<<str<<'\n';
    }
    else
    {
        AbstractHandler::handle(str);
    }
}

void CatHandler::handle(std::string str)
{
    if(str == "Meow")
    {
        std::cout<<str<<" "<<str<<'\n';
    }
    else
    {
        AbstractHandler::handle(str);
    }
}
