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
    double a,b,Fx;
    int n;
    std::cout<<"Please supply interval endpoints a and b (b>a) and a number of points n:"<<std::endl;
    std::cin>>a>>b>>n;

    assert(b>a&&n>0);//make sure that b>a and n>0.

    double xi;
    double Fx_old=FuncToMin(a);
    double Fx_star=Fx_old;
    double x_star=a;
    for(int i=1;i<n;i++)
    {
        xi=a+i*(b-a)/double(n-1);//calculate each xi.
        Fx=FuncToMin(xi);//try each xi in function f(x).
        if(Fx<Fx_old)
        {
            Fx_star=Fx;
            x_star=xi;//compare f(xi) with previous f(x)
        }
        Fx_old=Fx;
    }
    std::cout<<"The approximation to x* is "<<x_star<<std::endl;
    std::cout<<"The corresponding approximation to the minimum value of f(x*) is "<<Fx_star<<std::endl;

    return 0;
}

//Build the function of f(x)
double FuncToMin(double x)
{
    double Fx;
    Fx=x*(x-1)*exp(x);
    return Fx;
}


