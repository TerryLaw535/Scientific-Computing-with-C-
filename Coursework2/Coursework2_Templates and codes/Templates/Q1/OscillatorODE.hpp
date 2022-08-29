#ifndef OSCILLATORODE
#define OSCILLATORODE

#include "ODEInterface.hpp"

class OscillatorODE: public ODEInterface
{

  public:
      //Specialised constructor
      OscillatorODE(const double aVal);

      //Override the virtual method ComputeF in order to evaluate the right-hand side of (6)
      void ComputeF(const double t, const double x, double& f) const;

      //Override the virtual method ComputeAnalyticSolution in order to compute the exact solution to (3)-(4)
      void ComputeAnalyticSolution( const double t, double& x ) const;

  private:
      //Hiding default constructor
      OscillatorODE();

      //The parameter that will be used
      double mA;


};
#endif


