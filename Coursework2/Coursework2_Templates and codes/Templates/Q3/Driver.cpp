#include <iostream>
#include <cmath>
#include <cassert>
#include <fstream>

#include "OrbitODE.hpp"
#include "SymplecticEulerSolver.hpp"
#include "StoermerVerletSolver.hpp"
#include "ForwardEulerSolver.hpp"
#include "Vector.hpp"

int main(int argc, char* argv[])
{
    //Define the position of fixed point xp
    Vector* xFixed=new Vector(3);
    (*xFixed)(1)=0;
    (*xFixed)(2)=0;
    (*xFixed)(3)=0;

    //Instantiate an ODE system for test
    ODEInterface* p_ODESystem=new OrbitODE(5.972e24,*xFixed,6.378e6,1.737e6);

    //Define the initial state initialState,initial velocity initialVelocity, initial Period T0;
    Vector initialState=Vector(3);
    initialState(1)=3.844e8;
    initialState(2)=0;
    initialState(3)=0;

    Vector initialVelocity=Vector(3);
    initialVelocity(1)=0;
    initialVelocity(2)=sqrt((6.674e-11)*(5.972e24)/(3.844e8));
    initialVelocity(3)=0;

    //Here we can consider a period is that the initial time is 0 and final time is T0
    double T0=sqrt((4*pow(M_PI,2)*pow(3.844e8,3))/((6.674e-11)*(5.972e24)));

    //In order to have 10000 time step, we can set step size h=T0/10000;
    double h=T0/10000;

    //Instantiate a solver using three methods
    ForwardEulerSolver* p_forwardEuler_solver=new ForwardEulerSolver(*p_ODESystem,initialState,initialVelocity,0,T0,h,"ForwardEuler_Orbit.dat");
    SymplecticEulerSolver* p_symplecticEuler_solver=new SymplecticEulerSolver(*p_ODESystem,initialState,initialVelocity,0,T0,h,"SymplecticEuler_Orbit.dat");
    StoermerVerletSolver* p_StoermerVerlet_solver=new StoermerVerletSolver(*p_ODESystem,initialState,initialVelocity,0,T0,h,"StoermerVerletSolver_Orbit.dat");

    //Approximate solution
    p_forwardEuler_solver->Solve();
    p_symplecticEuler_solver->Solve();
    p_StoermerVerlet_solver->Solve();

    //Set that initial velocity=(0,0,0)
    initialVelocity(2)=0;

    //Since I choose the Stoermer-Verlet as the best method, hence I use it to try as the initial velocity changes.
    p_StoermerVerlet_solver->SetInitialVelocity(initialVelocity);
    p_StoermerVerlet_solver->SetOutputFileName("Collision test.dat");
    p_StoermerVerlet_solver->Solve();

    //Try some other initial velocities
    double k[4]={0.4,0.8,1.2,1.6};
    std::string fileName[4]={"Test k=0.4.dat","Test k=0.8.dat","Test k=1.2.dat","Test k=1.6.dat"};
    for(int i=0;i<4;i++)
    {
        std::cout<<"------------------------------------------------------"<<std::endl;
        std::cout<<"k="<<k[i];
        p_StoermerVerlet_solver->SetOutputFileName(fileName[i]);
        initialVelocity(2)=k[i]*sqrt((6.674e-11)*(5.972e24)/(3.844e8));
        p_StoermerVerlet_solver->SetInitialVelocity(initialVelocity);
        p_StoermerVerlet_solver->Solve();
    }



    // Clean
    delete xFixed;
    delete p_ODESystem;
    delete p_forwardEuler_solver;
    delete p_symplecticEuler_solver;
    delete p_StoermerVerlet_solver;
}
