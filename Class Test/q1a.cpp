#include <cstdlib>
#include <fstream>
#include <iostream>
#include <cmath>
#include <cassert>
#include <stdlib.h>
#include <chrono>
#include <vector>
double FuncToMin(double x);
int main(int argc, char* argv[])
{
    double x,Fx;
    std::cout<<"Please supply a value for x for the function f(x)=x*(x-1)*exp(x):"<<std::endl;
    std::cin>>x;//Ask the user for value of x
    Fx=FuncToMin(x);
    std::cout<<"f(x) = "<<Fx<<std::endl;
    return 0;
}

//Build the function of f(x)
double FuncToMin(double x)
{
    double Fx;
    Fx=x*(x-1)*exp(x);
    return Fx;
}
