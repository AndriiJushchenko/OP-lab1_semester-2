#ifndef SOLVEARCTAN_H
#define SOLVEARCTAN_H

#include <cmath>

class SolveArctan
{
private:
    double x;

public:
    SolveArctan(double inputX)
    {
        x = inputX;
    }

    double Calculate()
    {
        return std::atan(sqrt(x));
    }
};

#endif // SOLVEARCTAN_H
