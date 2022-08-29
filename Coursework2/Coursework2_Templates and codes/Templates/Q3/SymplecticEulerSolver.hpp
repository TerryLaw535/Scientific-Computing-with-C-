#ifndef SYMPLECTICEULERSOLVER
#define SYMPLECTICEULERSOLVER

#include "AbstractODESolver.hpp"
#include "ODEInterface.hpp"

class SymplecticEulerSolver:public AbstractODESolver
{
  public:

      //Specialised constructor
      SymplecticEulerSolver( ODEInterface & anODESystem ,
                          const Vector& initialState,
                          const Vector& initialVelocity,
                          const double initialTime,
                          const double finalTime,
                          const double stepSize,
                          const std::string outputFileName="output.dat",
                          const int saveGap=1,
                          const int printGap=1);

      //Using the symplectic Euler method for a first-order system of IVPs
      void Solve();

  private:

    //Hiding default constructor
    SymplecticEulerSolver();

};
#endif // SYMPLECTICEULERSOLVER
