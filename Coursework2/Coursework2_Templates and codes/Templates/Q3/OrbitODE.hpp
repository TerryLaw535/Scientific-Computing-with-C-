#ifndef ORBITODE
#define ORBITODE

#include "ODEInterface.hpp"

class OrbitODE: public ODEInterface
{

  public:
      //Specialised constructor
      OrbitODE(const double mpVal,const Vector& xpVal,const double rFixed,const double rMoving);

      //Override the virtual method ComputeF in order to evaluate the right-hand side of (6)
      void ComputeF(const double t, const Vector x, Vector& f) const;

      //Override the virtual method to check the collision
      bool DetectCollision(const double t, const Vector x) const;

  private:

      //Hiding default constructor
      OrbitODE();

      //The parameter that will be used.Here mMp denote the mass of fixed body,mpXp denote the pointer of the position of the fixed body
      double mMp;
      const Vector* mpXp;

      //mRFixed and mRMoving denote the radius of fixed body and moving body respectly
      double mRFixed;
      double mRMoving;

};
#endif
