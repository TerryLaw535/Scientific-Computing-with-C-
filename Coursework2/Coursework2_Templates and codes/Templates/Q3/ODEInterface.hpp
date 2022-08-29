#ifndef ODEINTERFACEHEADERDEF
#define ODEINTERFACEHEADERDEF

#include "Vector.hpp"

class ODEInterface
{

  public:

    // Compute right-hand side (pure virtual)
    virtual void ComputeF( const double t, const Vector x, Vector& f ) const = 0;

    // Compute analytical solution
    virtual void ComputeAnalyticSolution( const double t, Vector& x ) const;

    //Check whether the spherical bodies have collided during a time-step (pure virtual)
    virtual bool DetectCollision(const double t, const Vector x) const = 0;
};

#endif
