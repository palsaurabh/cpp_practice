#include <iostream>

/*Abstract factory design pattern is best understood by the example of 
different families of furniture like wooden, mettalic and modern etc.
Each family consists of similar objects like chair, table, cot etc. 
The major elements here are:
1. Abstract classes for each product type like chair, table cot etc.
    This class lists out all the mandatory method and features supported
    by each of these objects. For example, chair (number of legs, height,
     width etc). Major functionality like "sitting" for chair etc.
2. Abstract creator class. This class consists of factory
    methods for each product in the family. All the families have same 
    products but different style and different construction styles.
3. Concrete classes for each individual product like chair,table etc.
4. Concrete creator classes for each family.

*/

class product1 {
    public:
        virtual ~product1(){};
        virtual void product_desc() const = 0;
};

class concreteProduct1A : public product1{
    public:
        ~concreteProduct1A(){};
        void product_desc() const;
};

class concreteProduct1B : public product1{
    public:
        ~concreteProduct1B(){};
        void product_desc() const;
};

class product2 {
    public:
        virtual ~product2(){};
        virtual void product_desc() const = 0;
};

class concreteProduct2A : public product2{
    ~concreteProduct2A(){};
    void product_desc() const;
};

class concreteProduct2B : public product2{
    ~concreteProduct2B(){};
    void product_desc() const;
};

class productFamily {
    public:
        virtual ~productFamily(){};
        virtual product1 *createProduct1() = 0;
        virtual product2 *createProduct2() = 0;
        virtual void list_products(){
            this->p1 = createProduct1();
            this->p2 = createProduct2();
            std::cout<<"List of products in family\n";
            p1->product_desc();
            p2->product_desc();

            delete p1;
            delete p2;
        }
    protected:
        product1 * p1{nullptr};
        product2 * p2{nullptr};
};

class concreteProductFamilyA : public productFamily {
    public:
        ~concreteProductFamilyA(){};
        product1 *createProduct1();
        product2 *createProduct2();
};

class concreteProductFamilyB : public productFamily {
    public:
        ~concreteProductFamilyB(){};
        product1 *createProduct1();
        product2 *createProduct2();
};