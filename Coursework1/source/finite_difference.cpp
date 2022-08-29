#include <iostream>
#include <cmath>
#include "csr_matrix.hpp"

//The function to create A in LHS
csr_matrix A_LHS(int n)
{
    csr_matrix A;
    //According to the pde given by the question,I get the normal matrix of A and the CSR format
    A.no_rows=pow(n-1,2);//According to the new index given by the question, we can get the no_rows could be (n-1)^2-1+1=(n-1)^2
    A.issymmetric=1;//Here we store the matrix as symmetric
    A.row_start=new int[A.no_rows+1];
    int length=0;//use the length to count the length of matirx_entries and column_no
    A.row_start[0]=length;
    for(int i=1;i<=n-1;i++)
    {
        for(int j=1;j<=n-1;j++)
        {
            length++;
            //Since the matrix is symmetric, we only consider u(i+1,j) and u(i,j+1) here.
            if((i==n-1&&j!=n-1)||(i!=n-1&&j==n-1))//In this case u(i+1,j) or u(i,j+1) is 0, hence the length only plus 1
            {
                length++;
            }
            else if(i!=n-1&&j!=n-1)
            {
                length=length+2;
            }
            A.row_start[(i-1)*(n-1)+j]=length;
        }
    }
    //Then we set the matrix_entries and column_no.
    A.matrix_entries=new double[length];
    A.column_no=new int[length];
    int p=0;//Use p to count the index of matrix_entries and column_no
    for(int i=1;i<=n-1;i++)
    {
        for(int j=1;j<=n-1;j++)
        {
            A.matrix_entries[p]=4*pow(n,2)+1;//Since h=1/n, 1/h^2=n^2.Hence the entries in diagnal are 4*n^2+1
            A.column_no[p]=(i-1)*(n-1)+j-1;
            p++;
            if(i==n-1&&j!=n-1)
            {
                A.matrix_entries[p]=-pow(n,2);//The entries for u(i+1,j) or u(i,j+1) are -1/h^2=-n^2
                A.column_no[p]=(i-1)*(n-1)+j;
                p++;
            }
            else if(i!=n-1&&j==n-1)
            {
                A.matrix_entries[p]=-pow(n,2);
                A.column_no[p]=i*(n-1)+j-1;
                p++;
            }
            else if(i!=n-1&&j!=n-1)
            {
                A.matrix_entries[p]=-pow(n,2);
                A.column_no[p]=(i-1)*(n-1)+j;
                p++;
                A.matrix_entries[p]=-pow(n,2);
                A.column_no[p]=i*(n-1)+j-1;
                p++;
            }
        }
    }
    return A;
}

//The function to create the F in RHS
double* F_RHS(double(*f)(double x,double y),int n)
{
    int m=pow(n-1,2);//Get the length of F
    double* F=new double[m];
    for(int i=1;i<=n-1;i++)
    {
        for(int j=1;j<=n-1;j++)
        {
            F[(i-1)*(n-1)+(j-1)]=f(double(i)/double(n),double(j)/double(n));//Since x_i=ih and y_i=jh,and h=1/n
        }
    }
    return F;
}

//Define the general function f
double f(double x, double y)
{
    double f;double pi=M_PI;

    f=(2*pow(pi,2)+1)*sin(pi*x)*sin(pi*y);

    return f;
}

//Define a function to find the maximum element of the array,here n is the size of vector v.
double Max(double* v,int n)
{
    double m=v[0];
    for(int i=1;i<n;i++)
    {
        if(m<v[i])
        {
            m=v[i];
        }
    }
    return m;
}

