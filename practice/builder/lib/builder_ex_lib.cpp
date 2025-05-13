#include <iostream>
#include <string>
#include "builder_ex.hpp"
/**
 * Builder design pattern is useful when the product that needs to be created
 * is very complicated in the sense that it can be created in many different 
 * ways and exists in multiple combinations/configurations. For e.g. houses. Houses
 * can be customised in innumerable ways. We can have houses with different number of 
 * rooms, windows, material (wood, glass, metal). Etc.
 * 
 * For example:
 * Products created by builders could be Normal House, Palace (with Diamonds and stone) or
 * Wooden House. All with different builders following same steps. Different configurations
 * of these buildings can be obtained by having different combinations, like house with a 
 * pool or without.
 * 
 * Another example can be creating a car and a manual for the car. The steps of creating a 
 * car can be same as creating the manual for the car, because the manual also will be having
 * components and configuration as the car. So we see here that products are different but the
 * steps are same. Only difference will be the difference in the concreate Builder Implementation
 * for these products. The products created by the builders need not be of the same class type.
 * They can be different as we see above in case of palace, normal house or between the car
 * and manual.
 * 
 * We can also have a director which knows a few configurations of the car or house. It is 
 * agnostic of the actual product but knows the common builder interface only and runs the steps
 * based on some confgurations. For example 'small home' it can create just 1 room hall and kitchen.
 * For a medium size house it can create 2 rooms and 1 hall and 1 Kitchen etc. Similarly for cars 
 * as well
 * 
 * So each concrete builder class can return a product and is also derived from the base builder
 * class which defines all the steps needed for creating the product.
 * 
 * One big agenda we have to achieve is that the director or client code is agnostic of the type of
 * builder or the end product.
 * It builds the type of product based on the type of builder passed to it. This is achieved though
 * polymorphism
 */

/**
 * Palace Class.
 */
void Palace::listHouseDetails()
{
  std::cout<<"Windows:"<<numWindows<<'\n';
  std::cout<<"Bedrooms:"<<numBedrooms<<'\n';
  std::cout<<"HasPool?:"<<hasPool<<'\n';
  std::cout<<"material used:"<<static_cast<int>(use)<<'\n';
}
   
void House::listHouseDetails()
{
  std::cout<<"Windows:"<<numWindows<<'\n';
  std::cout<<"Bedrooms:"<<numBedrooms<<'\n';
  std::cout<<"HasPool?:"<<hasPool<<'\n';
  std::cout<<"material used:"<<static_cast<int>(use)<<'\n';
}


houseBuilder::houseBuilder()
{
  resetBuilder();
}

void houseBuilder::resetBuilder()
{
  house = new House();
}

void houseBuilder::cleanupBuilder()
{
}
void houseBuilder::createWindows(int num)
{
  house->numWindows = num;
}
void houseBuilder::createBedrooms(int num)
{
  house->numBedrooms = num;
}
void houseBuilder::addPool(bool val)
{
  house->hasPool = val;
}
void houseBuilder::setmaterialUsed(int num)
{
  if(num < static_cast<int>(House::material_used::max))
    house->use = static_cast<House::material_used>(num);
}
House *houseBuilder::getProduct()
{
  House *result = house;
  resetBuilder();          
  return result;
}
        
palaceBuilder::palaceBuilder()
{
  resetBuilder();
}

void palaceBuilder::resetBuilder()
{
  palace = new Palace();
}

void palaceBuilder::cleanupBuilder()
{
}
void palaceBuilder::createWindows(int num)
{
  palace->numWindows = num;
}
void palaceBuilder::createBedrooms(int num)
{
  palace->numBedrooms = num;
}
void palaceBuilder::addPool(bool val)
{
  palace->hasPool = val;
}
void palaceBuilder::setmaterialUsed(int num)
{
  if(num < static_cast<int>(Palace::material_used::max))
    palace->use = static_cast<Palace::material_used>(num);
}
Palace *palaceBuilder::getProduct()
{
  Palace *result = palace;
  resetBuilder();          
  return result;
}
shelterMakingDirector::shelterMakingDirector(buildShelterInterface &shelterObj)
{
  shelterObject = &shelterObj;
}

void shelterMakingDirector::createSmallShelter()
{
  shelterObject->createBedrooms(1);
  shelterObject->createWindows(2);
  shelterObject->setmaterialUsed(2);
  shelterObject->addPool(false);
}

void shelterMakingDirector::createLargeShelter()
{
  shelterObject->createBedrooms(4);
  shelterObject->createWindows(8);
  shelterObject->setmaterialUsed(1);
  shelterObject->addPool(true);
}
