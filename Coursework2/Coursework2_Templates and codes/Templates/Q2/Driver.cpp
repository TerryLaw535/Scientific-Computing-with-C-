#include <iostream>
#include <cmath>
#include <cassert>
#include <fstream>

#include "OscillatorODE.hpp"
#include "SymplecticEulerSolver.hpp"
#include "StoermerVerletSolver.hpp"

int main(int argc, char* argv[])
{
    //Instantiate an ODE system for test
    ODEInterface* p_ODESystem=new OscillatorODE(1.5);

    //Instantiate a solver using symplectic Euler method and Stoermer-Verlet method
    SymplecticEulerSolver* p_symplecticEuler_solver=new SymplecticEulerSolver(*p_ODESystem,0,1.5,0,30,0.01,"output_SymplecticEuler.dat");
    StoermerVerletSolver* p_StoermerVerlet_solver=new StoermerVerletSolver(*p_ODESystem,0,1.5,0,30,0.01,"output_StoermerVerlet.dat");

    //Approximate solution and compute the time respectively
    p_symplecticEuler_solver->Solve();
    p_StoermerVerlet_solver->Solve();


    //Set the final time T=1
    p_symplecticEuler_solver->SetFinalTime(1);
    p_StoermerVerlet_solver->SetFinalTime(1);

    //Define a set hVal to store various values of h
    double hVal[6]={0.0001,0.0002,0.00025,0.0004,0.0005,0.001};

    //Setting a file to save the data of h and Error
    std::ofstream output_file2;
    std::ofstream output_file3;

    //Opening file
    std::string file_name2="symplecticEuler_error.dat";
    std::string file_name3="StoermerVerlet_error.dat";
    output_file2.open(file_name2);
    output_file3.open(file_name3);
    assert(output_file2.is_open());
    assert(output_file3.is_open());

    //Define the error of symplectic Euler method and Stoermer-Verlet method
    double errorSymplecticEuler;
    double errorStoermerVerlet;

    //Start iteration
    for(int k=0;k<6;k++)
    {
        p_symplecticEuler_solver->SetStepSize(hVal[k]);
        p_StoermerVerlet_solver->SetStepSize(hVal[k]);
        errorSymplecticEuler=p_symplecticEuler_solver->ComputeError();
        errorStoermerVerlet=p_StoermerVerlet_solver->ComputeError();

        //Save the data
        output_file2<<hVal[k]<<" "<<errorSymplecticEuler<<std::endl;
        output_file3<<hVal[k]<<" "<<errorStoermerVerlet<<std::endl;
    }

    //Close file
    output_file2.close();
    output_file3.close();


    // Clean
    delete p_ODESystem;
    delete p_symplecticEuler_solver;
    delete p_StoermerVerlet_solver;
}
