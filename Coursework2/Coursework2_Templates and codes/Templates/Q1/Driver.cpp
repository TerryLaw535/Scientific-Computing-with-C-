#include <iostream>
#include <cmath>
#include <cassert>
#include <fstream>

#include "OscillatorODE.hpp"
#include "ForwardEulerSolver.hpp"

int main(int argc, char* argv[])
{
    //Instantiate an ODE system for test
    ODEInterface* p_ODESystem=new OscillatorODE(1.5);

    //Instantiate a solver using forward Euler method
    ForwardEulerSolver* p_forwardEuler_solver=new ForwardEulerSolver(*p_ODESystem,0,1.5,0,30,0.01,"output_ForwardEuler.dat");

    //Approximate solution
    p_forwardEuler_solver->Solve();

    //Set the final time T=1
    p_forwardEuler_solver->SetFinalTime(1);

    //Define a set hVal to store various values of h
    double hVal[6]={0.0001,0.0002,0.00025,0.0004,0.0005,0.001};

    //Setting a file to save the data of h and Error
    std::ofstream output_file2;

    //Opening file
    std::string file_name2="forwardEuler_error.dat";
    output_file2.open(file_name2);
    assert(output_file2.is_open());

    //Define the error of forward Euler method
    double errorForwardEuler;

    //Start iteration
    for(int k=0;k<6;k++)
    {
        p_forwardEuler_solver->SetStepSize(hVal[k]);
        errorForwardEuler=p_forwardEuler_solver->ComputeError();
        //Save the data
        output_file2<<hVal[k]<<" "<<errorForwardEuler<<std::endl;
    }

    //Close file
    output_file2.close();


    // Clean
    delete p_ODESystem;
    delete p_forwardEuler_solver;
}
