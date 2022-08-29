#include <cstdlib>
#include <fstream>
#include <iostream>
#include <cmath>
#include <cassert>
#include <stdlib.h>

double FuncToMin(double x);
int PerformGoldenSearch(double(*funcToMin)(double x), double a, double b,double tol,double& minimiser,double& numberIts);
int main(int argc, char* argv[])
{
    double a=0.0,b=1.0,tol=1.0e-10;
    double x_star,numberIts;
    int judge;
    //used to judge whether the maximum number of iterations has been reached.
    judge=PerformGoldenSearch(FuncToMin,a,b,tol,x_star,numberIts);
    if (judge==0)
    {
        std::cout<<"The approximation to x* is "<<x_star<<std::endl;
        std::cout<<"The corresponding approximation to the minimum value of f(x*) is "<<FuncToMin(x_star)<<std::endl;
        std::cout<<"The number of iteration required is "<<numberIts<<std::endl;
    }
    else
    {
        std::cout<<"The maximum number of iterations has been reached"<<std::endl;
    }


    return 0;
}
//Build the function of PerformGoldenSearch
int PerformGoldenSearch(double(*funcToMin)(double x), double a, double b,double tol,double& minimiser,double& numberIts)
{
    double x1,x2,x3,x4,MAX,mini;
    x1=a;
    x2=b;//initial x1 and x2
    numberIts=0;//The counter to calculate the number of iterations
    const double phi=(1.0+sqrt(5))/2.0;//Golden ratio
    while(numberIts<100)
    {
        if (fabs(x2-x1)<tol)
        {
            minimiser=(x1+x2)/2.0;
            break;
        }
        else
        {
            x3=(x2+phi*x1)/(1+phi);
            x4=(x1+phi*x2)/(1+phi);
            //find the max of f(x1) and f(x2),and the minimiser of f(x1) and f(x2)
            if(funcToMin(x1)>=funcToMin(x2))
            {
                MAX=funcToMin(x1);
                mini=x2;
            }
            else
            {
                MAX=funcToMin(x2);
                mini=x1;
            }
            if((funcToMin(x3)>MAX)&&(funcToMin(x4)>MAX))
            {
                minimiser=mini;
                break;
            }
            else
            {
                if(funcToMin(x3)<=funcToMin(x4))
                {
                    x2=x4;
                }
                else
                {
                    x1=x3;
                }
                numberIts++;
            }
        }

    }
    if(numberIts<100)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
//Build the function of f(x)
double FuncToMin(double x)
{
    double Fx;
    Fx=x*(x-1)*exp(x);
    return Fx;
}
