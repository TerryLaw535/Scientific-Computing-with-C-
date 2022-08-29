#ifndef ODEINTERFACEHEADERDEF
#define ODEINTERFACEHEADERDEF

#include <vector>
#include "Vector.hpp"

class ODEInterface
{

  public:

    // Compute right-hand side (pure virtual)
    virtual void ComputeF( const double t, const std::vector<Vector*> px, std::vector<Vector*> pf ) const = 0;

    // Compute analytical solution
    virtual void ComputeAnalyticSolution( const double t, std::vector<Vector*> px) const;

    //Check whether the spherical bodies have collided during a time-step (pure virtual)
    virtual bool DetectCollision(const double t, const std::vector<Vector*> px) const = 0;
};

#endif
