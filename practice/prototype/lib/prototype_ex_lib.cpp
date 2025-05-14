#include <iostream>
#include <string>
#include "prototype_ex.hpp"
/**
 * Prototype design pattern:
 * 
 * The prototype design pattern is used when you have a lot of different object types 
 * which have a long and complex inititalisation process and you need to create such objects 
 * often. So to avoid running the constructor for those classes again and again. We can use 
 * prototype design pattern.
 * 
 * Other use cases may be where, you need to copy objects where the class for the object is not
 * visible to us. Even if we know the object class, it is still not possible to copy the objects
 * as we may not have access to the private members of the object.
 * So basically it is not possible to create a copy of the object from outside completely.
 * 
 * In this case we need the object itself to create the copy for us. To do this, we can have 
 * the objects follow an interface which supports copying the class.
 * 
 * Usually the interface class for prototype only has one method called copy. This method is 
 * generally pure virtual and it has to be implemented by the respective classes supporting this 
 * copy functionality.
 * 
 * Also, a derived class of a derived protoype class needs to call the parents copy constructor to
 * fillup the parent part of the class and then fillup(copy) its own members.
 * 
 * In other words, Prototype design pattern lets us copy an object without having the need to know 
 * the class details of the object.
 *  */
// concretePrototype::concretePrototype(concretePrototype &cp)
// {
//   std::cout<<"Copy constructor called\n";
//   this->cp_att1 = cp.cp_att1;
//   this->cp_att2 = cp.cp_att2;
// }

Prototype *concretePrototype1::Clone()
{
  std::cout<<"Clone method of concretePrototype1 called\n";
  return new concretePrototype1(*this);
}

void concretePrototype1::printPrototype()
{
  std::cout<<"cp1_att:"<<cp1_att<<"prototypeName: "<<prototypeName<<"\n";
}

Prototype *concretePrototype2::Clone()
{
  std::cout<<"Clone method of concretePrototype2 called\n";
  return new concretePrototype2(*this);
}

void concretePrototype2::printPrototype()
{
  std::cout<<"cp2_att:"<<cp2_att<<"prototypeName: "<<prototypeName<<"\n";
}