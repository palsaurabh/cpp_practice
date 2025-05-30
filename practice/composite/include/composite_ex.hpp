#include <iostream>
#include <string>
#include <mutex>
#include <vector>
/**
 * Composite design pattern is used wherever we have a hierarchy of objects. 
 * For example in an Army. In Army there is hierarchy. Where there are different
 * levels of organisation from top to bottom. At the bottom there are Jawans, which
 * are considered are leaf object. 
 * Also another example can be taken as, graphic design. Here, leaf node are dots.
 * Using dots multiple different bigger objects can be created like circle, line or
 * any other shape. 
 * The basic funda in composite design pattern is that all the work is done by the
 * leaf nodes. Also the leaf node and the more complex nodes all follow the same 
 * interface.
 * We will implement a generic code where there are boxes inside boxes and boxes can
 * contain some items as well as other boxes. Each box price is equal to the price of
 * all the items plus price of all boxes in side the box. Final output of the code is
 * the price of the outermost box.
 * */

class IItem
{
    public:
        virtual int totalPrice() =  0;
};

class Item : public IItem
{
    private:
        int price;
    public:
        Item(int price):price{price}{}
        int totalPrice();
};

class Box : public IItem
{
    private:
        std::vector<IItem*> items;
    public:
        Box(std::vector<IItem*> &listofItems):items{listofItems}{};
        Box(IItem* box);
        Box& addItem(IItem* item);
        int totalPrice();
};