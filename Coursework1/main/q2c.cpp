#include <iostream>
#include <cmath>
#include <cassert>
#include <fstream>
#include <cstdlib>
#include "csr_matrix.hpp"
#include "linear_algebra.hpp"
int main(int argc, char* argv[])
{
    std::string file1="matrix2.dat";
    std::string file2="vector2.dat";
    //Get A,x and b by reading the file
    csr_matrix A=read_csrmatrix(file1);
    double* x=read_vector(file2);
    double* b=Ax_csr(A,x);
    double tol=1.0e-10;
    //Get the x_hat by the linear_algebra method
    double* x_hat=linear_algebra(A,b,tol);
    double* error_vec=linearCom(A.no_rows,-1,x,x_hat);
    double error_norm=vectorNorm2(A.no_rows,error_vec);
    std::cout<<std::endl;
    std::cout<<"The error ||x-x_hat||_2="<<error_norm<<std::endl;
    //Deallocate the memory
    delete[] x;
    delete[] b;
    delete[] x_hat;
    delete[] error_vec;
    Decsrmatrix(A);

    return 0;
}

