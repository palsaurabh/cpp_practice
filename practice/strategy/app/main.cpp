#include <iostream>
#include <string>
#include "composite_ex.hpp"
   
int main() {
  Item item(2);
  std::vector<IItem*>items;
  items.emplace_back(new Item{1});
  items.emplace_back(new Item{1});
  items.emplace_back(new Item{1});
  items.emplace_back(new Item{1});
  items.emplace_back(new Item{1});
  items.emplace_back(new Item{1});
  items.emplace_back(new Item{1});
  items.emplace_back(new Item{1});
  Box box{items};
  Box box1{&box};
  box1.addItem(new Item{1}).addItem(&box);
  std::cout<<"Final Price: "<<box1.totalPrice()<<"\n";
  return 0;
}
