#include <iostream>
#include <string>
#include <cmath>
#include "bridge_ex.hpp"
/**
 * Adapter design pattern:
 * Thread-unsafe version
 * */

    bool Hole::fits(const roundPeg &rp) const 
    {
        return radius > rp.getRadius();
    }

    int roundPeg::getRadius() const
    {
        return radius;
    }

    int squarePeg::getSide() const
    {
        return side;
    }

    int squarePegAdapter::getRadius() const
    {
        return sqPeg.getSide() * sqrt(2)/2;
    }
