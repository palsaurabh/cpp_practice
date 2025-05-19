#include <iostream>
#include <string>
#include <mutex>
/**
 * Bridge Pattern is used to divide complex classes into  */

/**
 */
class roundPeg;
 class Hole 
 {
    private:
        int radius;
    public:
        Hole(int radius):radius{radius}{}
        bool fits(const roundPeg &rp) const;
 };

class roundPeg
{
    private:
        int radius;
    public:
        roundPeg(int radius):radius{radius}{}
        virtual int getRadius() const ;
};

class squarePeg
{
    private:
        int side;
    public:
        squarePeg(int side):side{side}{}
        int getSide() const;
};

class squarePegAdapter : public roundPeg
{
    private:
        squarePeg sqPeg;
    public:
        squarePegAdapter(squarePeg sqPeg): roundPeg(0), sqPeg{sqPeg}{}
        int getRadius() const override;
};
