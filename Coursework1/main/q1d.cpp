#include <iostream>
#include <cmath>
#include "csr_matrix.hpp"
int main(int argc, char* argv[])
{
    csr_matrix A=csrformat_dissym();//Get the csr matrix without the assumption that the matrix is symmetric
    csr_matrix B=csrformat_sym();//Get the csr matrix with the assumption that the matrix is symmetric

    //Set up x
    double* x=new double[4];
    x[0]=6.0;
    x[1]=8.0;
    x[2]=2.0;
    x[3]=5.0;

    //Get the Ax without or with the assumption that matrix is symmetric respectively
    double* Ax_csrdissym;  double* Ax_csrsym;
    Ax_csrdissym=Ax_csr(A,x);
    Ax_csrsym=Ax_csr(B,x);

    //Print the different types of Ax
    std::cout<<"Ax without the assumption that matrix is symmetric"<<std::endl;
    for(int i=0;i<4;i++)
    {
        std::cout<<Ax_csrdissym[i]<<" ";
    }
    std::cout<<std::endl;
    std::cout<<"Ax with the assumption that matrix is symmetric"<<std::endl;
    for(int i=0;i<4;i++)
    {
        std::cout<<Ax_csrsym[i]<<" ";
    }
    std::cout<<std::endl;

    //Deallocate the memory
    Decsrmatrix(A);
    Decsrmatrix(B);
    delete[] x;
    delete[] Ax_csrsym;
    delete[] Ax_csrdissym;

    return 0;
}



