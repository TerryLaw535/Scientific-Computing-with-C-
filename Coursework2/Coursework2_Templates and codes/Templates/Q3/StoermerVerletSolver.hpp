#ifndef STOERMERVERLETSOLVER
#define STOERMERVERLETSOLVER

#include "AbstractODESolver.hpp"
#include "ODEInterface.hpp"

class StoermerVerletSolver:public AbstractODESolver
{
  public:

      //Specialised constructor
      StoermerVerletSolver( ODEInterface & anODESystem ,
                          const Vector& initialState,
                          const Vector& initialVelocity,
                          const double initialTime,
                          const double finalTime,
                          const double stepSize,
                          const std::string outputFileName="output.dat",
                          const int saveGap=1,
                          const int printGap=1);

      //Using the Stoermer-Verlet method for a first-order system of IVPs
      void Solve();

  private:

    //Hiding default constructor
    StoermerVerletSolver();

};
#endif // STOERMERVERLETSOLVER
