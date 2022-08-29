#include <cmath>
#include "OscillatorODE.hpp"

//Specialised constructor
OscillatorODE::OscillatorODE(const double aVal)
{
    mA=aVal;
}

// Compute the value of the right-hand side function
void OscillatorODE::ComputeF(const double t, const double x, double& f) const
{
    f=-pow(mA,2)*x;
}

// Compute the exact solution
void OscillatorODE::ComputeAnalyticSolution( const double t, double& x ) const
{
    x=sin(mA*t);
}

