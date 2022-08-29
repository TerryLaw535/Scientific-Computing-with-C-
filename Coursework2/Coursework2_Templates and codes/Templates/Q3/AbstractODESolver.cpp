#include <iomanip>
#include <sstream>
#include <string>
#include <cassert>
#include <fstream>

#include "AbstractODESolver.hpp"

//Printing an initial header
void AbstractODESolver::PrintHeader(const std::string solverName) const
{
    std::cout<<"---------------------------------------------------------"<<std::endl
    <<"Attempt to solve a second-order IVP using "<<solverName<<std::endl
    <<"with initial time "<<mInitialTime<<" and final time "<<mFinalTime<<std::endl
    <<"initial state x("<<mInitialTime<<")="
    <<"("<<mpInitialState->Read(0)<<","<<mpInitialState->Read(1)<<","<<mpInitialState->Read(2)
    <<") and initial velocity v("<<mInitialTime<<")="
    <<"("<<mpInitialVelocity->Read(0)<<","<<mpInitialVelocity->Read(1)<<","<<mpInitialVelocity->Read(2)<<")"<<std::endl
    <<"step size h= "<<mStepSize<<", saveGap="<<mSaveGap<<", printGap="<<mPrintGap<<std::endl
    <<"---------------------------------------------------------"<<std::endl;
}

//Print infos every printGap iterations
void AbstractODESolver::PrintIteration(const double t, const Vector x,const Vector v) const
{
    std::cout<<t<<"   ("<<(&x)->Read(0)<<","<<(&x)->Read(1)<<","<<(&x)->Read(2)<<")    "
    <<"("<<(&v)->Read(0)<<","<<(&v)->Read(1)<<","<<(&x)->Read(2)<<")"<<std::endl;
}

//Save infos every saveGap iterations
void AbstractODESolver::SaveIteration(const double t, const Vector x,const Vector v) const
{
    //Setting the output file
    std::ofstream output_file;

    //Setting the name of the file and open it
    std::string file_name=mOutputFileName;
    output_file.open(file_name,std::ios::app);
    assert(output_file.is_open());

    //Here I don't use the format like (x1,x2,x3) and just save as x1 x2 x3 in order to help RStudio(which use to plot) to recognize
    output_file<<t<<" "<<(&x)->Read(0)<<" "<<(&x)->Read(1)<<" "<<(&x)->Read(2)<<" "
            <<" "<<(&v)->Read(0)<<" "<<(&v)->Read(1)<<" "<<(&v)->Read(2)<<" "<<std::endl;

    output_file.close();
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

//Set the initial state
void AbstractODESolver::SetInitialState(const Vector& initialState)
{
    mpInitialState=&initialState;
}

//Set the initial velocity
void AbstractODESolver::SetInitialVelocity(const Vector& initialVelocity)
{
    mpInitialVelocity=&initialVelocity;
}

//Set the output file's name
void AbstractODESolver::SetOutputFileName(const std::string outputFileName)
{
    mOutputFileName=outputFileName;
}

