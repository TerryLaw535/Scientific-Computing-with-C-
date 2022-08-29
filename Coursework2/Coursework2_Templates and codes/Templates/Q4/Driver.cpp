#include <iostream>
#include <cmath>
#include <cassert>
#include <fstream>
#include <vector>
#include <chrono>

#include "NBodyODE.hpp"
#include "StoermerVerletSolver.hpp"
#include "Vector.hpp"

int main(int argc, char* argv[])
{
    //Define the initial position and velocity of the bodies in this system
    Vector EarthState(3);
    EarthState(1)=0;
    EarthState(2)=0;
    EarthState(3)=0;

    Vector EarthVelocity(3);
    EarthVelocity(1)=0;
    EarthVelocity(2)=0;
    EarthVelocity(3)=0;

    Vector MoonState(3);
    MoonState(1)=3.844e8;
    MoonState(2)=0;
    MoonState(3)=0;

    Vector MoonVelocity(3);
    MoonVelocity(1)=0;
    MoonVelocity(2)=sqrt((6.674e-11)*(5.972e24)/(3.844e8));
    MoonVelocity(3)=0;

    //Put the initial position into a set.Here earth is the body 1 and moon is the body 2
    std::vector<Vector*> vec_pInitialState={&EarthState,&MoonState};
    std::vector<Vector*> vec_pInitialVelocity={&EarthVelocity,&MoonVelocity};

    //Define the parameter that will be used
    std::vector<double> mVal={5.972e24,7.342e22};
    std::vector<double> rVal={6.378e6,1.737e6};

    //Instantiate an ODE system for test
    ODEInterface* p_ODESystem=new NBodyODE(mVal,rVal);

    //Here we can consider a period is that the initial time is 0 and final time is T0
    double T0=sqrt((4*pow(M_PI,2)*pow(3.844e8,3))/((6.674e-11)*(5.972e24)));

    //In order to have 10000 time step, we can set step size h=T0/10000;
    double h=T0/10000;

    //In this question I need to set printGap,saveGap and OutputFileName to help me plot trajectory easily
    //Instantiate a solver using Stoermer-Verlet method
    StoermerVerletSolver* p_StoermerVerlet_solver=new StoermerVerletSolver(*p_ODESystem,vec_pInitialState,vec_pInitialVelocity,0,T0,h,"Earth-Moon.dat",1,1000);
    std::cout<<"Earth-Moon System:"<<std::endl;
    p_StoermerVerlet_solver->Solve();

    //To answer question 4(b)ii, I choose the solar system inner planet [Sun,Mercury,Venus,Earth,Mars]
    std::vector<double> mSolarSystem={1.9891e30,3.301e23,4.8675e24,5.972e24,6.417e23};//Mass of solar system(kg)
    //Because there are many factors affect the stable of the solar system, here I consider the bodies are point masses(r=0) to prevent the collision.
    std::vector<double> rSolarSystem={0,0,0,0,0};
    std::vector<double> VelocitySolarSystem={0,4.787e4,3.500e4,2.978e4,2.413e4};//The scalar of the velocity(m/s)
    std::vector<double> StateSolarsystem={0,5.791e10,1.082e11,1.496e11,2.2794e11};//The average distance form body to sun(m)

    std::vector<Vector*> vec_pInitialStateSolar(5);
    std::vector<Vector*> vec_pInitialVelocitySolar(5);

    for(int i=0;i<5;i++)
    {
        vec_pInitialStateSolar[i]=new Vector(3);
        vec_pInitialVelocitySolar[i]=new Vector(3);
        (*vec_pInitialStateSolar[i])(1)=StateSolarsystem[i];
        (*vec_pInitialStateSolar[i])(2)=0;
        (*vec_pInitialStateSolar[i])(3)=0;
        (*vec_pInitialVelocitySolar[i])(1)=0;
        (*vec_pInitialVelocitySolar[i])(2)=VelocitySolarSystem[i];
        (*vec_pInitialVelocitySolar[i])(3)=0;
    }

    //Here I choose the period of Mar(s)
    double T_Mars=5.94e7;
    double h2=T_Mars/1e5;

    ODEInterface* p_ODESystem2=new NBodyODE(mSolarSystem,rSolarSystem);
    StoermerVerletSolver Solarsystem_solver((*p_ODESystem2),vec_pInitialStateSolar,vec_pInitialVelocitySolar,0,T_Mars,h2,"SolarSystem.dat",1,1000);
    std::cout<<"-----------------------------------------------------------------------------"<<std::endl;
    std::cout<<"Solar System:"<<std::endl;
    (&Solarsystem_solver)->Solve();

    //Then I test the N body system for N={2,4,8,16,32,64}
    int N[6]={2,4,8,16,32,64};
    //Set the final time T_bodis and stepsize h3
    double T_bodies=1e6;
    double h3=T_bodies/1e5;
    for(int k=0;k<6;k++)
    {
        std::cout<<"-----------------------------------------------------------------------------"<<std::endl;
        std::cout<<"N="<<N[k]<<std::endl;
        std::vector<double> mBodies(N[k]);//Mass of the bodies
        std::vector<double> rBodies(N[k]);//Radius of the bodies
        std::vector<Vector*> vec_pInitialStateBodies(N[k]);
        std::vector<Vector*> vec_pInitialVelocityBodies(N[k]);
        for(int i=0;i<N[k];i++)
        {
            //Since for question 4(b)iii, I just need to compute the time.
            //Hence I just need to let the bodies to be point masses(r=0) so that I can compute the time of the complete system.
            mBodies[i]=1e10;
            rBodies[i]=0;
            vec_pInitialStateBodies[i]=new Vector(3);
            vec_pInitialVelocityBodies[i]=new Vector(3);
            (*vec_pInitialStateBodies[i])(1)=i*(1e8);
            (*vec_pInitialStateBodies[i])(2)=0;
            (*vec_pInitialStateBodies[i])(3)=0;
            (*vec_pInitialVelocityBodies[i])(1)=0;
            (*vec_pInitialVelocityBodies[i])(2)=i*(1e6);
            (*vec_pInitialVelocityBodies[i])(3)=0;
        }
        ODEInterface* p_ODESystem3=new NBodyODE(mBodies,rBodies);
        StoermerVerletSolver NBodies_solver((*p_ODESystem3),vec_pInitialStateBodies,vec_pInitialVelocityBodies,0,T_bodies,h3,"NBodies.dat",1e5,1e5);
        //Compute the time
        // Store the initial time point in t0
        std::chrono::high_resolution_clock::time_point t0=std::chrono::high_resolution_clock::now();

        NBodies_solver.Solve();

        // Store the final time point in t1
        std::chrono::high_resolution_clock::time_point t1=std::chrono::high_resolution_clock::now();
        // Report t1 -t0 (in milliseconds )
        std::cout<<std::endl<<" Time elapsed : "
        << std::chrono::duration_cast <std::chrono::milliseconds>(t1-t0).count()
         << " milliseconds " << std :: endl ;

         //Clean to prevent memory leak
         delete p_ODESystem3;
         for(int i=0;i<N[k];i++)
         {
             delete vec_pInitialStateBodies[i];
             delete vec_pInitialVelocityBodies[i];
         }
    }

    // Clean
    delete p_ODESystem;
    delete p_StoermerVerlet_solver;
    for(int i=0;i<5;i++)
    {
        delete vec_pInitialStateSolar[i];
        delete vec_pInitialVelocitySolar[i];
    }

}
