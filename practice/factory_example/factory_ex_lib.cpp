#include <iostream>
#include <string>
#include "factory_ex.hpp"
/**
 * The Product interface declares the operations that all concrete products must
 * implement.
 */

/**
* Concrete Products provide various implementations of the Product interface.
*/

  std::string ConcreteProduct1::Operation() const{
    return "{Result of the ConcreteProduct1}";
  }

  std::string ConcreteProduct2::Operation() const{
    return "{Result of the ConcreteProduct2}";
  }
   /**
    * The Creator class declares the factory method that is supposed to return an
    * object of a Product class. The Creator's subclasses usually provide the
    * implementation of this method.
    */
   
  std::string Creator::SomeOperation() const{
    // Call the factory method to create a Product object.
    Product* product = this->FactoryMethod();
    // Now, use the product.
    std::string result = "Creator: The same creator's code has just worked with " + product->Operation();
    delete product;
    return result;
  }
   
  Product* ConcreteCreator1::FactoryMethod() const {
    return new ConcreteProduct1();
  }
  Product* ConcreteCreator2::FactoryMethod() const {
    return new ConcreteProduct2();
  }