#include <gtest/gtest.h>
#include "builder_ex.hpp"

class BuilderExampleTest : public ::testing::Test {
    protected:
        void SetUp() override {
            std::cout<<"Setting up test environment...\n";
        }
        void TearDown() override {
            std::cout<<"Cleaning up test environemnt...\n";
        }
};

TEST_F(BuilderExampleTest, HouseReturnsCorrectDetails){
  std::stringstream details{}; 
  details<<"Windows:"<<1<<'\n';
  details<<"Bedrooms:"<<2<<'\n';
  details<<"HasPool?:"<<0<<'\n';
  details<<"material used:"<<0<<'\n';
  House *house = new House();
  EXPECT_EQ(house->listShelterDetails(), details.str());
}

TEST_F(BuilderExampleTest, PalaceReturnsCorrectDetails){
  std::stringstream details{}; 
  details<<"Windows:"<<1<<'\n';
  details<<"Bedrooms:"<<2<<'\n';
  details<<"HasPool?:"<<0<<'\n';
  details<<"material used:"<<0<<'\n';
  Palace *house = new Palace();
  EXPECT_EQ(house->listShelterDetails(), details.str());
}

TEST_F(BuilderExampleTest, HouseBuilderReturnsCorrectDetails){
  std::stringstream details{}; 
  details<<"Windows:"<<2<<'\n';
  details<<"Bedrooms:"<<1<<'\n';
  details<<"HasPool?:"<<0<<'\n';
  details<<"material used:"<<1<<'\n';
  houseBuilder Builder;
  shelterMakingDirector *Director = new shelterMakingDirector(Builder);
  Director->createSmallShelter();
  House *house = Builder.getProduct();
  EXPECT_EQ(house->listShelterDetails(), details.str());
}

TEST_F(BuilderExampleTest, PalaceBuilderReturnsCorrectDetails){
  std::stringstream details{}; 
  details<<"Windows:"<<8<<'\n';
  details<<"Bedrooms:"<<4<<'\n';
  details<<"HasPool?:"<<1<<'\n';
  details<<"material used:"<<1<<'\n';
  palaceBuilder Builder;
  shelterMakingDirector *Director = new shelterMakingDirector(Builder);
  Director->createLargeShelter();
  Palace *palace = Builder.getProduct();
  EXPECT_EQ(palace->listShelterDetails(), details.str());
}