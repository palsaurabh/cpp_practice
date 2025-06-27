#include <iostream>
#include <string>
#include <mutex>
#include <vector>
/**
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