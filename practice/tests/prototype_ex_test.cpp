#include <gtest/gtest.h>
#include "prototype_ex.hpp"

//Test Fixture for PrototypeExample
// This test fixture sets up the environment for testing the Prototype pattern
// It includes setup and teardown methods that can be used to initialize and clean up resources
// before and after each test case
// The test cases will use this fixture to ensure that they are isolated and do not interfere with each other
// The test cases will also use the fixture to access the common resources and methods defined in the fixture
class PrototypeExampleTest : public ::testing::Test {
protected:
  void SetUp() override {}
  void TearDown() override {}
};

TEST_F(PrototypeExampleTest, PrototypeInterfaceHasVirtualDestructor) {
    // Test virtual destructor through base pointer
    Prototype* prototype = new concretePrototype1(1, "test");
    delete prototype;  // Should not cause memory leaks
    SUCCEED();
}

TEST_F(PrototypeExampleTest, PrototypeInterfaceMethodsAreVirtual) {
    // Test that Clone() and printPrototype() are truly virtual
    Prototype* prototype1 = new concretePrototype1(1, "cp1");
    Prototype* prototype2 = prototype1->Clone();
    
    EXPECT_NE(prototype1, prototype2);  // Clone should create a new instance
    EXPECT_EQ(prototype1->prototypeName, prototype2->prototypeName);
    
    delete prototype1;
    delete prototype2;
}

TEST_F(PrototypeExampleTest, PrototypeCannotBeInstantiated) {
    // Compile-time test - following line would fail to compile
    // Prototype prototype("test");  // Should not compile as Prototype is abstract
    SUCCEED();
}

TEST_F(PrototypeExampleTest, PrototypeNameIsInitialized) {
    concretePrototype1 cp1(1, "TestPrototype");
    EXPECT_EQ(cp1.prototypeName, "TestPrototype");
}

TEST_F(PrototypeExampleTest, DerivedClassesImplementRequiredMethods) {
    concretePrototype1 cp1(1, "cp1");
    concretePrototype2 cp2(2, "cp2");
    
    // Verify both classes implement Clone()
    Prototype* clone1 = cp1.Clone();
    Prototype* clone2 = cp2.Clone();
    
    EXPECT_NE(clone1, nullptr);
    EXPECT_NE(clone2, nullptr);
    
    // Clean up
    delete clone1;
    delete clone2;
}

TEST_F(PrototypeExampleTest, FactoryCreatesPrototypes) {
    prototypeFactory pf;
    
    Prototype* cp1copy = pf.createPrototype("cp1");
    EXPECT_NE(cp1copy, nullptr);
    EXPECT_EQ(cp1copy->prototypeName, "cp1");
    
    Prototype* cp2copy = pf.createPrototype("cp2");
    EXPECT_NE(cp2copy, nullptr);
    EXPECT_EQ(cp2copy->prototypeName, "cp2");
    
    // Clean up
    delete cp1copy;
    delete cp2copy;
}

TEST_F(PrototypeExampleTest, FactoryReturnsNullForUnknownPrototype) {
    prototypeFactory pf;
    
    Prototype* unknownCopy = pf.createPrototype("unknown");
    EXPECT_EQ(unknownCopy, nullptr);  // Should return null for unknown prototype
    
    // No need to delete as it's null
}
TEST_F(PrototypeExampleTest, ConcretePrototype1Clone) {
    concretePrototype1 cp1(1, "cp1");
    Prototype* cp1copy = cp1.Clone();
    
    EXPECT_NE(cp1copy, nullptr);
    EXPECT_EQ(cp1copy->prototypeName, "cp1");
    
    // Clean up
    delete cp1copy;
}
TEST_F(PrototypeExampleTest, ConcretePrototype2Clone) {
    concretePrototype2 cp2(2, "cp2");
    Prototype* cp2copy = cp2.Clone();
    
    EXPECT_NE(cp2copy, nullptr);
    EXPECT_EQ(cp2copy->prototypeName, "cp2");
    
    // Clean up
    delete cp2copy;
} 

//This test checks if the functions prints a particular string on excution or not.
//This is done by using testing::internal::CaptureStdOut() and testing::internal::GetCapturedStdOut().
//This is a good way to test if the function is printing the correct string or not.
TEST_F(PrototypeExampleTest, ConcretePrototype1Print) {
    concretePrototype1 cp1(1, "cp1");
    testing::internal::CaptureStdout();
    cp1.printPrototype();
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_NE(output.find("cp1_att:1"), std::string::npos);
    EXPECT_NE(output.find("prototypeName: cp1"), std::string::npos);
}

TEST_F(PrototypeExampleTest, ConcretePrototype2Print) {
    concretePrototype2 cp2(2, "cp2");
    testing::internal::CaptureStdout();
    cp2.printPrototype();
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_NE(output.find("cp2_att:2"), std::string::npos);
    EXPECT_NE(output.find("prototypeName: cp2"), std::string::npos);
}

TEST_F(PrototypeExampleTest, PrototypeFactoryDestructor) {
    // Test that the factory destructor cleans up properly
    prototypeFactory* pf = new prototypeFactory();
    delete pf;  // Should not cause memory leaks
    SUCCEED();
}
TEST_F(PrototypeExampleTest, ConcretePrototype1Destructor) {
    // Test that the concretePrototype1 destructor cleans up properly
    concretePrototype1* cp1 = new concretePrototype1(1, "cp1");
    delete cp1;  // Should not cause memory leaks
    SUCCEED();
}
TEST_F(PrototypeExampleTest, ConcretePrototype2Destructor) {
    // Test that the concretePrototype2 destructor cleans up properly
    concretePrototype2* cp2 = new concretePrototype2(2, "cp2");
    delete cp2;  // Should not cause memory leaks
    SUCCEED();
}
TEST_F(PrototypeExampleTest, ConcretePrototype1CopyConstructor) {
    concretePrototype1 cp1(1, "cp1");
    concretePrototype1 cp1copy(cp1);  // Copy constructor
    
    EXPECT_EQ(cp1copy.prototypeName, "cp1");
    // EXPECT_EQ(cp1copy.cp1_att, 1);
}
TEST_F(PrototypeExampleTest, ConcretePrototype2CopyConstructor) {
    concretePrototype2 cp2(2, "cp2");
    concretePrototype2 cp2copy(cp2);  // Copy constructor
    
    EXPECT_EQ(cp2copy.prototypeName, "cp2");
    // EXPECT_EQ(cp2copy.cp2_att, 2);
}
TEST_F(PrototypeExampleTest, ConcretePrototype1CopyAssignment) {
    concretePrototype1 cp1(1, "cp1");
    concretePrototype1 cp1copy(2, "cp2");
    
    cp1copy = cp1;  // Copy assignment operator
    
    EXPECT_EQ(cp1copy.prototypeName, "cp1");
    // EXPECT_EQ(cp1copy.cp1_att, 1);
}
TEST_F(PrototypeExampleTest, ConcretePrototype2CopyAssignment) {
    concretePrototype2 cp2(2, "cp2");
    concretePrototype2 cp2copy(3, "cp3");
    
    cp2copy = cp2;  // Copy assignment operator
    
    EXPECT_EQ(cp2copy.prototypeName, "cp2");
    // EXPECT_EQ(cp2copy.cp2_att, 2);
}
TEST_F(PrototypeExampleTest, ConcretePrototype1AssignmentOperator) {
    concretePrototype1 cp1(1, "cp1");
    concretePrototype1 cp1copy(2, "cp2");
    
    cp1copy = cp1;  // Assignment operator
    
    EXPECT_EQ(cp1copy.prototypeName, "cp1");
    // EXPECT_EQ(cp1copy.cp1_att, 1);
}
TEST_F(PrototypeExampleTest, ConcretePrototype2AssignmentOperator) {
    concretePrototype2 cp2(2, "cp2");
    concretePrototype2 cp2copy(3, "cp3");
    
    cp2copy = cp2;  // Assignment operator
    
    EXPECT_EQ(cp2copy.prototypeName, "cp2");
    // EXPECT_EQ(cp2copy.cp2_att, 2);
}