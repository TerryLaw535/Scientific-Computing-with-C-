#include <cmath>
#include <cassert>
#include "OrbitODE.hpp"

//Specialised constructor
OrbitODE::OrbitODE(const double mpVal,const Vector& xpVal,const double rFixed,const double rMoving)
{
    mMp=mpVal;
    mpXp=&xpVal;
    mRFixed=rFixed;
    mRMoving=rMoving;
}

// Compute the value of the right-hand side function
void OrbitODE::ComputeF(const double t, const Vector x, Vector& f) const
{
    //Calculate the distance from moving body to fixed body |xp-x| denoted as r and xp-x denote as r_vec
    Vector r_vec=(*mpXp)-x;
    double r=(&r_vec)->CalculateNorm(2);
    f=r_vec*((6.674e-11)*mMp/pow(r,3));
}

//Check whether the spherical bodies have collided during a time-step
bool OrbitODE::DetectCollision(const double t,const Vector x) const
{
    bool Collision=0;
    //Calculate the distance from moving body to fixed body |xp-x| denoted as r and xp-x denote as r_vec
    Vector r_vec=(*mpXp)-x;
    double r=(&r_vec)->CalculateNorm(2);

    //Check whether the collision happens
    if (mRFixed+mRMoving>=r)
    {
        Collision=1;
    }

    return Collision;
}

