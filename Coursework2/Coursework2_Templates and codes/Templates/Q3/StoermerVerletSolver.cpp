#include <iostream>
#include <cassert>
#include <cmath>
#include <fstream>

#include "StoermerVerletSolver.hpp"

//Specialised constructor
StoermerVerletSolver::StoermerVerletSolver ( ODEInterface & anODESystem ,
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
void StoermerVerletSolver::Solve()
{
    // Print header (inherited from abstract class) in order to provide info about the initial value of t,x and v
    std::string solverName="Stoermer-Verlet method";
    PrintHeader(solverName);

    //Setting the initial value of t,x and v
    double t=mInitialTime;
    Vector x=(*mpInitialState);
    Vector v=(*mpInitialVelocity);

    //Define the right-hand side function of (6) f and compute it in initial time
    Vector f(3);
    mpODESystem->ComputeF(t,x,f);

    //Setting the output file
    std::ofstream output_file;

    //Setting the name of the file and open it
    std::string file_name=mOutputFileName;
    output_file.open(file_name,std::ios::app);
    assert(output_file.is_open());

    //Save and print the initial value of t,x and v
    PrintIteration(t,x,v);
    SaveIteration(t,x,v);

    //Define a iterator n
    int n=0;

    //Define the f_new that will be used in iteration
    Vector f_new(3);

    //Start iterations
    while(t<=mFinalTime)
    {
        //Iteration
        x=x+v*mStepSize+f*0.5*pow(mStepSize,2);
        t=t+mStepSize;
        mpODESystem->ComputeF(t,x,f_new);
        v=v+((f)+(f_new))*0.5*mStepSize;
        f=f_new;
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

        //Print the selected elements of x and v
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

