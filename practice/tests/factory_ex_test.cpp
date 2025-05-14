#include <gtest/gtest.h>
#include "factory_ex.hpp"

class FactoryExampleTest : public ::testing::Test {
protected:
  void SetUp() override {}
  void TearDown() override {}
};

TEST_F(FactoryExampleTest, ConcreteProduct1ReturnsCorrectString) {
  ConcreteProduct1 product;
  EXPECT_EQ(product.Operation(), "{Result of the ConcreteProduct1}");
}

TEST_F(FactoryExampleTest, ConcreteProduct2ReturnsCorrectString) {
  ConcreteProduct2 product;
  EXPECT_EQ(product.Operation(), "{Result of the ConcreteProduct2}");
}

TEST_F(FactoryExampleTest, ConcreteCreator1CreatesCorrectProduct) {
  ConcreteCreator1 creator;
  Product* product = creator.FactoryMethod();
  EXPECT_EQ(product->Operation(), "{Result of the ConcreteProduct1}");
  delete product;
}

TEST_F(FactoryExampleTest, ConcreteCreator2CreatesCorrectProduct) {
  ConcreteCreator2 creator;
  Product* product = creator.FactoryMethod();
  EXPECT_EQ(product->Operation(), "{Result of the ConcreteProduct2}");
  delete product;
}

TEST_F(FactoryExampleTest, Creator1SomeOperationReturnsCorrectString) {
  ConcreteCreator1 creator;
  std::string expected = "Creator: The same creator's code has just worked with {Result of the ConcreteProduct1}";
  EXPECT_EQ(creator.SomeOperation(), expected);
}

TEST_F(FactoryExampleTest, Creator2SomeOperationReturnsCorrectString) {
  ConcreteCreator2 creator;
  std::string expected = "Creator: The same creator's code has just worked with {Result of the ConcreteProduct2}";
  EXPECT_EQ(creator.SomeOperation(), expected);
}

TEST_F(FactoryExampleTest, FactoryMethodReturnsValidPointer) {
  ConcreteCreator1 creator1;
  ConcreteCreator2 creator2;
  
  Product* product1 = creator1.FactoryMethod();
  Product* product2 = creator2.FactoryMethod();
  
  EXPECT_NE(product1, nullptr);
  EXPECT_NE(product2, nullptr);
  
  delete product1;
  delete product2;
}

// ...existing code...

TEST_F(FactoryExampleTest, ProductsFromSameCreatorAreDifferentInstances) {
    ConcreteCreator1 creator;
    Product* product1 = creator.FactoryMethod();
    Product* product2 = creator.FactoryMethod();
    
    EXPECT_NE(product1, product2);
    
    delete product1;
    delete product2;
}

TEST_F(FactoryExampleTest, ProductsFromDifferentCreatorsHaveDifferentBehavior) {
    ConcreteCreator1 creator1;
    ConcreteCreator2 creator2;
    
    Product* product1 = creator1.FactoryMethod();
    Product* product2 = creator2.FactoryMethod();
    
    EXPECT_NE(product1->Operation(), product2->Operation());
    
    delete product1;
    delete product2;
}

TEST_F(FactoryExampleTest, CreatorPolymorphismWorks) {
    Creator* creator1 = new ConcreteCreator1();
    Creator* creator2 = new ConcreteCreator2();
    
    EXPECT_NE(creator1->SomeOperation(), creator2->SomeOperation());
    
    delete creator1;
    delete creator2;
}

TEST_F(FactoryExampleTest, ProductPolymorphismWorks) {
    Product* product1 = new ConcreteProduct1();
    Product* product2 = new ConcreteProduct2();
    
    EXPECT_NE(product1->Operation(), product2->Operation());
    
    delete product1;
    delete product2;
}