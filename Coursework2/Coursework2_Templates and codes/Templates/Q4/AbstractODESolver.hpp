#ifndef ABSTRACTODESOLVERHEADERDEF
#define ABSTRACTODESOLVERHEADERDEF

#include <vector>
#include "ODEInterface.hpp"
#include "Vector.hpp"

class AbstractODESolver
{
    protected:

        //Initial and final times
        double mInitialTime;
        double mFinalTime;

        //ODE system under consideration
        ODEInterface* mpODESystem;

        //Time-step size h
        double mStepSize;

        //Initial state x(t^0)
        const std::vector<Vector*>* mpVec_pInitialState;

        //initialVelocity v(t^0)
        const std::vector<Vector*>* mpVec_pInitialVelocity;

        //The name of the output file
        std::string mOutputFileName;

        //Value of save gap and print gap
        int mSaveGap;
        int mPrintGap;


    public:

        //Pure virtual method to solve the IVPs
        virtual void Solve()=0;

        //Set value of final time
        void SetFinalTime(const double finalTime);

        //Set value of step size
        void SetStepSize(const double stepSize);

        //Set the initial state
        void SetInitialState(const std::vector<Vector*>& mpVec_pInitialState);

        //Set the initial Velocity
        void SetInitialVelocity(const std::vector<Vector*>& mpVec_pInitialVelocity);

        //Set the output file's name
        void SetOutputFileName(const std::string outputFileName);

        //Print the current iteration. In this question I only print the x to observe the trajectory
        void PrintIteration(const double t,const std::vector<Vector*> px) const;

        //Save the current iteration. In this question I only save the x to help plot the trajectory
        void SaveIteration(const double t,const std::vector<Vector*> px) const;

};
#endif // ABSTRACTODESOLVERHEADERDEF
