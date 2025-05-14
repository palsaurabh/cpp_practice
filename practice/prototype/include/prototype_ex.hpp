#include <iostream>
#include <string>
#include <unordered_map>
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

/**
 * Create a prototype class interface
 */

class Prototype
{
  public:
    std::string prototypeName;
    Prototype(std::string name): prototypeName{name}{}
    virtual ~Prototype(){}
    virtual Prototype *Clone() = 0;
    virtual void printPrototype() = 0;

};
/*
* concretePrototype1 Class
*/
class concretePrototype1 : public Prototype
{
  private:
    int cp1_att;
  public:
    concretePrototype1(int att1, std::string prototypeName): Prototype{prototypeName}, cp1_att{att1}{}
    // concretePrototype(concretePrototype &cp);//Copy constructor is not needed as the class does not have any pointers
    Prototype* Clone() override;
    void printPrototype() override;
};

/*
* ConcretePrototype2 Class
*/
class concretePrototype2: public Prototype
{
  private :
    int cp2_att;
  public:
  concretePrototype2(int attr1, std::string prototypeName):Prototype{prototypeName},cp2_att{attr1} {}
  Prototype* Clone() override;
  void printPrototype() override;
};

class prototypeFactory
{
  private:
    std::unordered_map<std::string, Prototype*> prototypes_;
  public:
    prototypeFactory()
    {
      prototypes_["cp1"] = new concretePrototype1(1, "cp1");
      prototypes_["cp2"] = new concretePrototype2(2, "cp2");
    }

    Prototype *createPrototype(const std::string &prototypeName)
    {
      if (prototypes_.find(prototypeName) != prototypes_.end())
      {
        return prototypes_[prototypeName]->Clone();
      }
      return nullptr;
    }

    ~prototypeFactory()
    {
      for (auto &pair : prototypes_)
      {
        delete pair.second;
      }
    }
};

