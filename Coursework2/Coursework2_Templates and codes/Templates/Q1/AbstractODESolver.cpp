#include <cassert>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>

#include "AbstractODESolver.hpp"

//Printing an initial header
void AbstractODESolver::PrintHeader(const std::string solverName) const
{
    std::cout<<"---------------------------------------------------------"<<std::endl
    <<"Attempt to solve a second-order IVP using "<<solverName<<std::endl
    <<"with initial time "<<mInitialTime<<" and final time "<<mFinalTime<<std::endl
    <<"initial state x("<<mInitialTime<<")="<<mInitialState<<" and initial velocity v("<<mInitialTime<<")="<<mInitialVelocity<<std::endl
    <<"step size h= "<<mStepSize<<", saveGap="<<mSaveGap<<", printGap="<<mPrintGap<<std::endl
    <<"---------------------------------------------------------"<<std::endl;
}

//Print infos every printGap iterations
void AbstractODESolver::PrintIteration( const double t,const double x,const double v) const
{
    std::cout<<t<<"   "<<x<<"   "<<v<<std::endl;
}

//Set value of final time
void AbstractODESolver::SetFinalTime(const double finalTime)
{
    mFinalTime=finalTime;
}

//Set value of step size
void AbstractODESolver::SetStepSize(const double stepSize)
{
    mStepSize=stepSize;
}



