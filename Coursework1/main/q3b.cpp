#include <iostream>
#include <cmath>
#include "csr_matrix.hpp"
#include "linear_algebra.hpp"
#include "finite_difference.hpp"

int main(int argc, char* argv[])
{
    int N[5]={16,32,64,128,256};//Set the array of n
    //Declare all the variables that will be used
    csr_matrix A;double* F;double tol=1.0e-10;
    double* u_hat;double* u_max=new double[5];
    for(int i=0;i<5;i++)
    {
        std::cout<<"Case n="<<N[i]<<std::endl;
        A=A_LHS(N[i]);
        F=F_RHS(f,N[i]);
        u_hat=linear_algebra(A,F,tol);
        u_max[i]=Max(u_hat,A.no_rows);
        std::cout<<"u_max as n="<<N[i]<<" is "<<u_max[i]<<std::endl;
        std::cout<<std::endl;
    }
    //Put all the u_max in the end in order to check easily.
    std::cout<<"To sum up:"<<std::endl;
    for(int i=0;i<5;i++)
    {
        std::cout<<"u_max as n="<<N[i]<<" is "<<u_max[i]<<std::endl;
    }
    //Deallocate the memory
    Decsrmatrix(A);
    delete[] F;
    delete[] u_hat;
    delete[] u_max;

    return 0;
}
