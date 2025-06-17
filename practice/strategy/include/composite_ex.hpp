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

#include <iostream>
#include <vector>
#include <complex>
#include <tuple>
#include <cmath>
#include <limits>
using namespace std;

struct DiscriminantStrategy
{
    virtual double calculate_discriminant(double a, double b, double c) = 0;
};

struct OrdinaryDiscriminantStrategy : DiscriminantStrategy
{
    double calculate_discriminant(double a, double b, double c) override
    {
        //(b2 -4ac)
        return (b*b - 4*a*c);
    }
};

struct RealDiscriminantStrategy : DiscriminantStrategy
{
    //b2 - -4ac
    double calculate_discriminant(double a, double b, double c) override
    {
        double d = (b*b - 4*a*c);
        if(d < 0)
            return std::numeric_limits<double> ::quiet_NaN();
        else
            return d;
    }
        
        
};

class QuadraticEquationSolver
{
    DiscriminantStrategy& strategy;
public:
    QuadraticEquationSolver(DiscriminantStrategy &strategy) : strategy(strategy) {}

    tuple<complex<double>, complex<double>> solve(double a, double b, double c)
    {
        double discriminant = strategy.calculate_discriminant(a, b, c);
        complex<double> sqrt_disc = sqrt(complex<double>(discriminant, 0));
        complex<double> root1 = (-b + sqrt_disc) / (2.0 * a);
        complex<double> root2 = (-b - sqrt_disc) / (2.0 * a);
        return make_tuple(root1, root2);
    }
};