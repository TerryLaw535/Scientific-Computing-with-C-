#ifndef ABSTRACTODESOLVERHEADERDEF
#define ABSTRACTODESOLVERHEADERDEF

#include "ODEInterface.hpp"

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
        double mInitialState;

        //initialVelocity v(t^0)
        double mInitialVelocity;

        //The name of the output file
        std::string mOutputFileName;

        //Value of save gap and print gap
        int mSaveGap;
        int mPrintGap;


    public:

        //Pure virtual method to solve the IVPs
        virtual void Solve()=0;

        //Pure virtual method to compute the error
        virtual double ComputeError()=0;

        //Set value of final time
        void SetFinalTime(const double finalTime);

        //Set value of step size
        void SetStepSize(const double stepSize);

        //Print an initial header
        virtual void PrintHeader(const std::string solverName) const;

        //Print Infos of the current iteration
        virtual void PrintIteration(const double t,const double x,const double v) const;

};
#endif // ABSTRACTODESOLVERHEADERDEF
