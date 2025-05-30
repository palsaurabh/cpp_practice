#include <iostream>
#include <string>
#include <cmath>
#include "composite_ex.hpp"
/**
 * Composite Design Pattern
 * */

int Item::totalPrice()
{
    return price;
}

int Box::totalPrice()
{
    int total = 0;
    for (auto item : items)
        total += item->totalPrice();
    return total;
}

Box& Box::addItem(IItem* item)
{
    items.emplace_back(item);
    return *this;
}

Box::Box(IItem* box)
{
    this->addItem(box);
}
