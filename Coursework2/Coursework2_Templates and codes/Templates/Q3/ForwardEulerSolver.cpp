#include <iostream>
#include <cassert>
#include <cmath>
#include <fstream>

#include "ForwardEulerSolver.hpp"

//Specialised constructor
ForwardEulerSolver::ForwardEulerSolver ( ODEInterface & anODESystem ,
                          const Vector& initialState,
                          const Vector& initialVelocity,
                          const double initialTime,
                          const double finalTime,
                          const double stepSize,
                          const std::string outputFileName,
                          const int saveGap,
                          const int printGap)
{
    //Initialising protected variables inherited from AbstractODESolver
    mInitialTime=initialTime;
    mFinalTime=finalTime;
    mpODESystem=&anODESystem;
    assert(stepSize>0);//Make sure that the value of step size is bigger than 0
    mStepSize=stepSize;
    mpInitialState=&initialState;
    mpInitialVelocity=&initialVelocity;
    mOutputFileName=outputFileName;
    assert(saveGap>=0 && printGap>=0);//Make sure that the value of saveGap and printGap is nonnegative
    mSaveGap=saveGap;
    mPrintGap=printGap;
}

//Solution method
void ForwardEulerSolver::Solve()
{
    // Print header (inherited from abstract class) in order to provide info about the initial value of t,x and v
    std::string solverName="forward Euler method";
    PrintHeader(solverName);

    //Setting the initial value of t,x and v
    double t=mInitialTime;
    Vector x=(*mpInitialState);
    Vector v=(*mpInitialVelocity);

    //Define the right-hand side function of (6) f
    Vector f(3);

    //Setting the output file
    std::ofstream output_file;

    //Setting the name of the file and open it
    std::string file_name=mOutputFileName;
    output_file.open(file_name,std::ios::app);
    assert(output_file.is_open());


    //Save and prin the initial value of t, x and v
    PrintIteration(t,x,v);
    SaveIteration(t,x,v);

    //Define a iterator n
    int n=0;

    //Start iterations
    while(t<=mFinalTime)
    {
        //Iteration
        mpODESystem->ComputeF(t,x,f);
        x=x+v*mStepSize;
        v=v+f*mStepSize;
        t=t+mStepSize;
        n++;

        //Determine whether collision happens
        bool isCollision=mpODESystem->DetectCollision(t,x);
        if(isCollision)
        {
            std::cout<<"Collision happens after "<<int(t/60)<<" minutes and at this time x=("
            <<(&x)->Read(0)<<","<<(&x)->Read(1)<<","<<(&x)->Read(2)<<")"<<std::endl;
            //Stop the code running
            system("pause");
            break;
        }

        //Print the selected elements of t,x and v
        if(n%mPrintGap==0)
        {
            PrintIteration(t,x,v);
        }

        if(n%mSaveGap==0)
        {
            SaveIteration(t,x,v);
        }
    }

    //Close file
    output_file.close();

}

