#include <iostream>
#include <cmath>
#include <cassert>
#include "csr_matrix.hpp"

//Dot product of two vectors
double dotProduct(int n,double* v,double* w)
{
    double vw=0;
    for(int i=0;i<n;i++)
    {
        vw+=v[i]*w[i];
    }
    return vw;
}

//2-norm of a vector
double vectorNorm2(int n,double* v)
{
    double sum=0;
    for(int i=0;i<n;i++)
    {
        sum+=pow(v[i],2);
    }
    sum=sqrt(sum);
    return sum;
}

//linear combination u+aw
double* linearCom(int n,double a,double* u,double* w)
{
    double* com=new double[n];
    for(int i=0;i<n;i++)
    {
        com[i]=u[i]+a*w[i];
    }
    return com;
}

//The function that is used to solve the linear algebra problem
double* linear_algebra(csr_matrix A,double* b,double tol)
{
   int n=A.no_rows;//The size of the vector and matrix
   //Set x0
   double* x=new double[n];
   for(int i=0;i<n;i++)
   {
       x[i]=0;
   }
   //Set r0 and p0
   double* r; double* p;
   r=linearCom(n,-1,b,Ax_csr(A,x));
   p=r;
   //Declare the variables that will be used in the iteration
   int k=0;
   double* Ap;double* r_new;double alpha;double beta;
   //Apply the given iteration
   while(vectorNorm2(n,r)>tol)
   {
       std::cout<<"As the iteration time k="<<k<<", the 2-norm of rk is"<<vectorNorm2(n,r)<<std::endl;
       Ap=Ax_csr(A,p);
       alpha=dotProduct(n,r,r)/dotProduct(n,p,Ap);
       x=linearCom(n,alpha,x,p);
       r_new=linearCom(n,-alpha,r,Ap);
       beta=dotProduct(n,r_new,r_new)/dotProduct(n,r,r);
       p=linearCom(n,beta,r_new,p);
       r=r_new;
       k++;
   }
   //Deallocate all the memory I have set up
   return x;
   delete[] Ap;
   delete[] r_new;
   delete[] r;
   delete[] p;
}

//The function that is used to use Preconditioned iterative methods to solve the linear algebra problem
double* preconditioned(csr_matrix A,double* b,double tol)
{
   int n=A.no_rows;//The size of the vector and matrix
   //To get b_new=(P^-1)b
   double* b_new=new double[n];
   for(int i=0;i<n;i++)
   {
      //If there is 0 in the diagonal component of A,the inverse of P does not exist.Hence we have to make sure that all component in the diagonal of A is not 0;
      //But in the linear system in this question, the elements of the diagonal of A is 4*n^2+1 which is impossible to be 0.
      assert(A.column_no[A.row_start[i]]==i);//Here if the column no of the element in every row's start is equal to i(row no),then it means all elements in the diagonal are nonzero
      b_new[i]=(1/A.matrix_entries[A.row_start[i]])*b[i];
   }
   //To get A_new=(P^-1)*A.A_new is almost equal to A except the matrix entries.
   csr_matrix A_new;
   A_new.issymmetric=1;//In the linear system of this question, the elements of the diagonal of A must be equal so that P^-1*A is symmetric
   A_new.no_rows=A.no_rows;
   A_new.column_no=A.column_no;
   A_new.row_start=A.row_start;
   int length=A.row_start[A.no_rows];//Get the length of matrix_entries and column_no
   A_new.matrix_entries=new double[length];
   for(int i=0;i<A_new.no_rows;i++)
   {
       for(int j=A_new.row_start[i];j<A_new.row_start[i+1];j++)
       {
           A_new.matrix_entries[j]=(1/A.matrix_entries[A.row_start[i]])*A.matrix_entries[j];
       }
   }
   //Set x0
   double* x=new double[n];
   for(int i=0;i<n;i++)
   {
       x[i]=0;
   }
   //Set r0 and p0
   double* r; double* p;
   r=linearCom(n,-1,b_new,Ax_csr(A_new,x));
   p=r;
   //Declare the variables that will be used in the iteration
   int k=0;
   double* Ap;double* r_new;double alpha;double beta;
   //Apply the given iteration
   while(vectorNorm2(n,r)>tol)
   {
       std::cout<<"As the iteration time k="<<k<<", the 2-norm of rk is "<<vectorNorm2(n,r)<<std::endl;
       Ap=Ax_csr(A_new,p);
       alpha=dotProduct(n,r,r)/dotProduct(n,p,Ap);
       x=linearCom(n,alpha,x,p);
       r_new=linearCom(n,-alpha,r,Ap);
       beta=dotProduct(n,r_new,r_new)/dotProduct(n,r,r);
       p=linearCom(n,beta,r_new,p);
       r=r_new;
       k++;
   }
   return x;
   //Deallocate all the memory I have set up
   delete[] Ap;
   delete[] r_new;
   delete[] r;
   delete[] p;
   Decsrmatrix(A_new);
   delete[] b_new;
   return x;
}
