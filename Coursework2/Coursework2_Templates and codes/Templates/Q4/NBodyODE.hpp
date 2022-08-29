#ifndef NBODYODE
#define NBODYODE

#include <vector>
#include "ODEInterface.hpp"

class NBodyODE: public ODEInterface
{

  public:
      //Specialised constructor
      NBodyODE(const std::vector<double> mVal,const std::vector<double> rVal);

      //Override the virtual method ComputeF in order to evaluate the right-hand side of (6)
      void ComputeF(const double t, const std::vector<Vector*> x, std::vector<Vector*> f) const;

      //Override the virtual method to check the collision
      bool DetectCollision(const double t, const std::vector<Vector*> x) const;

  private:

      //Hiding default constructor
      NBodyODE();

      //mM denote the set of mass of all bodies
      std::vector<double> mM;

      //mR denote the set of radius of all bodies
      std::vector<double> mR;

};
#endif
