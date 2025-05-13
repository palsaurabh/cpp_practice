#include <iostream>
#include <string>
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
 * Create two Product Classes.
 * There will be one Palace Class and one House Class
 * 
 */

/**
 * Palace Class.
 */

 class Palace {
    public:
      int numWindows{1};
      int numBedrooms{2};
      bool hasPool{false};
      enum class material_used
      {
        diamonds = 0,
        precious_stones = 1,
        max = 2,
      };
      material_used use{material_used::diamonds};
      void listHouseDetails();
};
   
/*
* House Class
*/
 class House {
    public:
      int numWindows{1};
      int numBedrooms{2};
      bool hasPool{false};
      enum class material_used
      {
        bricks = 0,
        wood = 1,
        max = 2,
      };
      material_used use{material_used::bricks};
      void listHouseDetails();
};


  /**
   * Interface Class Builder 
   */

   class buildShelterInterface
   {
      public:
        virtual void resetBuilder() = 0;
        virtual void createWindows(int num) = 0;
        virtual void createBedrooms(int num) = 0;
        virtual void addPool(bool val) = 0;
        virtual void setmaterialUsed(int num) = 0;
   };

   class houseBuilder : public buildShelterInterface
   {
      public:
        House *house;
        houseBuilder();
        void resetBuilder();
        void cleanupBuilder();
        void createWindows(int num);
        void createBedrooms(int num);
        void addPool(bool val);
        void setmaterialUsed(int num);
        House *getProduct();
   };

   class palaceBuilder : public buildShelterInterface
   {
      public:
        Palace *palace;
        palaceBuilder();
        void resetBuilder();
        void cleanupBuilder();
        void createWindows(int num);
        void createBedrooms(int num);
        void addPool(bool val);
        void setmaterialUsed(int num);
        Palace *getProduct();
  };
   
/**
 * Class ShelterMakingDirector
 */
class shelterMakingDirector
{
  public:
     shelterMakingDirector(buildShelterInterface &shelterObj);     
     void createSmallShelter();
     void createLargeShelter();
  private:
     buildShelterInterface *shelterObject;
};