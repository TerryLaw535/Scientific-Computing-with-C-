#include <iostream>
#include <cassert>
#include <cmath>
#include <fstream>

#include "StoermerVerletSolver.hpp"

//Specialised constructor
StoermerVerletSolver::StoermerVerletSolver ( ODEInterface & anODESystem ,
                          const std::vector<Vector*> &vec_pInitialState,
                          const std::vector<Vector*> &vec_pInitialVelocity,
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
    mpVec_pInitialState=&vec_pInitialState;
    mpVec_pInitialVelocity=&vec_pInitialVelocity;
    mOutputFileName=outputFileName;
    assert(saveGap>=0 && printGap>=0);//Make sure that the value of saveGap and printGap is nonnegative
    mSaveGap=saveGap;
    mPrintGap=printGap;
}

//Solution method
void StoermerVerletSolver::Solve()
{

    //Setting the initial value of t.In this question I use the array of the pointer of x and v.
    double t=mInitialTime;
    std::vector<Vector*> px=(*mpVec_pInitialState);
    std::vector<Vector*> pv=(*mpVec_pInitialVelocity);

    //Define the array of right-hand side function of (18) f and compute it in initial time
    //Here I use the array of the pointer pf

    std::vector<Vector*> pf(px.size());
    for(int i=0;i<px.size();i++)
    {
        pf[i]=new Vector(3);
    }
    mpODESystem->ComputeF(t,px,pf);

    //Setting the output file
    std::ofstream output_file;

    //Setting the name of the file and open it
    std::string file_name=mOutputFileName;
    output_file.open(file_name,std::ios::app);
    assert(output_file.is_open());

    //Save and print the initial value of t,x and v
    PrintIteration(t,px);
    SaveIteration(t,px);

    //Define a iterator n, printStep and saveStep to help print and save data
    int n=0;

    //Define the pf_new that will be used in iteration
    std::vector<Vector*> pf_new(px.size());
    for(int i=0;i<px.size();i++)
    {
        pf_new[i]=new Vector(3);
    }

    //Start iterations
    while(t<=mFinalTime)
    {
        //Iteration
        for(int i=0;i<px.size();i++)
        {
            (*px[i])=(*px[i])+(*pv[i])*mStepSize+(*pf[i])*0.5*pow(mStepSize,2);
        }
        t=t+mStepSize;
        mpODESystem->ComputeF(t,px,pf_new);
        for(int i=0;i<pv.size();i++)
        {
            (*pv[i])=(*pv[i])+((*pf[i])+(*pf_new[i]))*0.5*mStepSize;
        }
        pf=pf_new;
        n++;

        //Determine whether collision happens
        bool isCollision=mpODESystem->DetectCollision(t,px);
        if(isCollision)
        {
            std::cout<<"Collision happens after "<<int(t/60)<<" minites and the state of the system is:"<<std::endl;
            for(int i=0;i<px.size();i++)
            {
                std::cout<<"("<<(px[i])->Read(0)<<","<<(px[i])->Read(1)<<","<<(px[i])->Read(2)<<") ";
            }
            std::cout<<std::endl;

            //Stop the code from running
            system("pause");
            break;
        }

        //Print the selected elements of x and v
        if(n%mPrintGap==0)
        {
            PrintIteration(t,px);
        }

        if(n%mSaveGap==0)
        {
            SaveIteration(t,px);
        }
    }

    //Close file
    output_file.close();

}
