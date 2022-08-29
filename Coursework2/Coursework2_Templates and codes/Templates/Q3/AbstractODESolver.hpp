#ifndef ABSTRACTODESOLVERHEADERDEF
#define ABSTRACTODESOLVERHEADERDEF

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
        const Vector* mpInitialState;

        //initialVelocity v(t^0)
        const Vector* mpInitialVelocity;

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
        void SetInitialState(const Vector& initialState);

        //Set the initial Velocity
        void SetInitialVelocity(const Vector& initialVelocity);

        //Set the output file's name
        void SetOutputFileName(const std::string outputFileName);

        //Print an initial header
        virtual void PrintHeader(const std::string solverName) const;

        //Save infos of the current iteration
        virtual void SaveIteration(const double t,const Vector x,const Vector v) const;

        //Print Infos of the current iteration
        virtual void PrintIteration(const double t,const Vector x,const Vector v) const;

};
#endif // ABSTRACTODESOLVERHEADERDEF
