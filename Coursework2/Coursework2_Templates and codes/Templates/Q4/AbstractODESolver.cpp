#include <iomanip>
#include <sstream>
#include <string>
#include <cassert>
#include <fstream>

#include "AbstractODESolver.hpp"

//Print infos every printGap iterations
void AbstractODESolver::PrintIteration(const double t, const std::vector<Vector*> px) const
{
    std::cout<<t<<" ";
    for(int i=0;i<px.size();i++)
    {
        std::cout<<"("<<(px[i])->Read(0)<<","<<(px[i])->Read(1)<<","<<(px[i])->Read(2)<<") ";
    }
    std::cout<<std::endl;
}

//Save infos every printGap iterations
void AbstractODESolver::SaveIteration(const double t,const std::vector<Vector*> px) const
{
    //Setting the output file
    std::ofstream output_file;

    //Setting the name of the file and open it
    std::string file_name=mOutputFileName;
    output_file.open(file_name,std::ios::app);
    assert(output_file.is_open());

    output_file<<t<<" ";

    for(int i=0;i<px.size();i++)
    {
        output_file<<(px[i])->Read(0)<<" "<<(px[i])->Read(1)<<" "<<(px[i])->Read(2)<<" ";
    }
    output_file<<std::endl;
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
void AbstractODESolver::SetInitialState(const std::vector<Vector*>& vec_pInitialState)
{
    mpVec_pInitialState=&vec_pInitialState;
}

//Set the initial velocity
void AbstractODESolver::SetInitialVelocity(const std::vector<Vector*>& vec_pInitialVelocity)
{
    mpVec_pInitialVelocity=&vec_pInitialVelocity;
}

//Set the output file's name
void AbstractODESolver::SetOutputFileName(const std::string outputFileName)
{
    mOutputFileName=outputFileName;
}
