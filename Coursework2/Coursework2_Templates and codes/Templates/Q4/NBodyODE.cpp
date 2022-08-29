#include <cmath>
#include <cassert>
#include <iostream>
#include "NBodyODE.hpp"

//Specialised constructor
NBodyODE::NBodyODE(const std::vector<double> mVal,const std::vector<double> rVal)
{
    assert(mVal.size()==rVal.size());
    mM=mVal;
    mR=rVal;
}


// Compute the value of the right-hand side function
void NBodyODE::ComputeF(const double t, const std::vector<Vector*> px, std::vector<Vector*> pf) const
{
    //Define the distance from xj to xi |xj-xi| denoted as r and xj-xi denote as r_vec
    Vector r_vec(3);
    double r;

    for(int i=0;i<px.size();i++)
    {
        (*pf[i])(1)=0;
        (*pf[i])(2)=0;
        (*pf[i])(3)=0;
        for(int j=0;j<px.size();j++)
        {
            if(i!=j)
            {
                r_vec=(*px[j])-(*px[i]);
                r=r_vec.CalculateNorm(2);
                (*pf[i])=(*pf[i])+r_vec*(((6.674e-11)*mM[j])/pow(r,3));
            }
        }
    }
}

//Check whether the spherical bodies have collided during a time-step
bool NBodyODE::DetectCollision(const double t,const std::vector<Vector*> px) const
{
    bool Collision=0;
    //Define the distance from xj to xi |xj-xi| denoted as r and xj-xi denote as r_vec
    Vector r_vec(3);
    double r;

    //Check whether the collision happens
    for(int i=0;i<px.size();i++)
    {
        for(int j=0;j<px.size();j++)
        {
            if(i!=j)
            {
                //Calculate the distance between body i and body j
                r_vec=(*px[j])-(*px[i]);
                r=r_vec.CalculateNorm(2);
                if(mR[i]+mR[j]>=r)
                {
                   Collision=1;
                }
            }
        }
    }
    return Collision;
}
