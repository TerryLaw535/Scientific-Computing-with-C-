#include <iostream>
#include <cmath>
#include <cassert>
#include <fstream>
#include <cstdlib>
struct csr_matrix
{
    //Define the matrix_entries column_no and row_start
    double* matrix_entries;
    int* column_no;
    int* row_start;
    //Store the number of rows of the matrix and whether or not the matrix is being stored as a symmetric matrix
    int no_rows;
    bool issymmetric;
};

//Set up CSR format of A without the assumption that the matrix is symmetric
csr_matrix csrformat_dissym()
{
    csr_matrix A;
    A.no_rows=4;
    A.issymmetric=0;
    A.matrix_entries=new double[8];
    A.column_no=new int[8];
    A.row_start=new int[5];
    //Set up matrix entries
    A.matrix_entries[0]=8.0;
    A.matrix_entries[1]=2.0;
    A.matrix_entries[2]=3.0;
    A.matrix_entries[3]=1.0;
    A.matrix_entries[4]=4.0;
    A.matrix_entries[5]=2.0;
    A.matrix_entries[6]=1.0;
    A.matrix_entries[7]=7.0;
    //Set up column no
    A.column_no[0]=0;
    A.column_no[1]=3;
    A.column_no[2]=1;
    A.column_no[3]=3;
    A.column_no[4]=2;
    A.column_no[5]=0;
    A.column_no[6]=1;
    A.column_no[7]=3;
    //Set up row start
    A.row_start[0]=0;
    A.row_start[1]=2;
    A.row_start[2]=4;
    A.row_start[3]=5;
    A.row_start[4]=8;

    return A;

}

//Set up CSR format of A with the assumption that the matrix is symmetric
csr_matrix csrformat_sym()
{
    csr_matrix A;
    A.no_rows=4;
    A.issymmetric=1;
    A.matrix_entries=new double[6];
    A.column_no=new int[6];
    A.row_start=new int[5];
    //Set up matrix entries
    A.matrix_entries[0]=8.0;
    A.matrix_entries[1]=2.0;
    A.matrix_entries[2]=3.0;
    A.matrix_entries[3]=1.0;
    A.matrix_entries[4]=4.0;
    A.matrix_entries[5]=7.0;
    //Set up column no
    A.column_no[0]=0;
    A.column_no[1]=3;
    A.column_no[2]=1;
    A.column_no[3]=3;
    A.column_no[4]=2;
    A.column_no[5]=3;
    //Set up row start
    A.row_start[0]=0;
    A.row_start[1]=2;
    A.row_start[2]=4;
    A.row_start[3]=5;
    A.row_start[4]=6;

    return A;

}

//The function that used to deallocate the csr_matrix
void Decsrmatrix(csr_matrix& A)
{
    //deallocate the memory
    delete[] A.matrix_entries;
    delete[] A.column_no;
    delete[] A.row_start;
}

double* Ax_csr(csr_matrix A,double* x)
{
    double* Ax=new double[A.no_rows];
    //Calculate Ax without the assumption that A is symmetric
    if(A.issymmetric==0)
    {
        for(int i=0;i<A.no_rows;i++)
        {
            Ax[i]=0;
            for(int j=A.row_start[i];j<A.row_start[i+1];j++)
            {
                Ax[i]+=A.matrix_entries[j]*x[A.column_no[j]];
            }
        }
    }
    //Calculate Ax with the assumption that A is symmetric
    else
    {
        for(int k=0;k<A.no_rows;k++)//Initialize Ax
        {
            Ax[k]=0;
        }
        for(int i=0;i<A.no_rows;i++)
        {
            for(int j=A.row_start[i];j<A.row_start[i+1];j++)
            {
                Ax[i]+=A.matrix_entries[j]*x[A.column_no[j]];
                //Add the symmetric part
                if(A.column_no[j]!=i)
                {
                    Ax[A.column_no[j]]+=A.matrix_entries[j]*x[i];
                }
            }
        }
    }

    return Ax;
}


csr_matrix read_csrmatrix(std::string file)
{
    csr_matrix A;
    //We read file matrix1
    std::ifstream read_file;//Define input stream
    read_file.open(file);//Open file
    assert(read_file.is_open());//Check file is open
    std::string line;//string to read full line into

    std::getline(read_file,line);//Read "Symmetric (1 for symmetric, 0 for not symmetric)"
    std::getline(read_file,line);//Read issymmetric
    A.issymmetric=bool(atoi(line.c_str()));

    std::getline(read_file,line);//Read "Number Rows"
    std::getline(read_file,line);//Read noRows
    A.no_rows=atoi(line.c_str());

    std::getline(read_file,line);//Read "Number Nonzeros"
    std::getline(read_file,line);//Read noNonzeros
    int noNonzeros=atoi(line.c_str());

    std::getline(read_file,line);//Read "row_start"
    A.row_start=new int[A.no_rows+1];
    for(int i=0;i<=A.no_rows;i++)
    {
        std::getline(read_file,line);//Read
        A.row_start[i]=atoi(line.c_str());
    }

    std::getline(read_file,line);//Read "column_no"
    A.column_no=new int[noNonzeros];
    for(int i=0;i<noNonzeros;i++)
    {
        std::getline(read_file,line);//Read
        A.column_no[i]=atoi(line.c_str());
    }

    std::getline(read_file,line);//Read "matrix_entries"
    A.matrix_entries=new double[noNonzeros];
    for(int i=0;i<noNonzeros;i++)
    {
        std::getline(read_file,line);//Read
        A.matrix_entries[i]=atof(line.c_str());
    }
    read_file.close();

    return A;
}

double* read_vector(std::string file)
{
    //We read vector1
    std::ifstream read_file;//Define input stream
    read_file.open(file);
    assert(read_file.is_open());//Check file is open
    std::string line;//string to read full line into

    std::getline(read_file,line);//Read "Vector length"
    std::getline(read_file,line);//Read vector_length
    int vector_length=atoi(line.c_str());

    std::getline(read_file,line);//Read "Vector entries"
    double* v=new double[vector_length];
    for(int i=0;i<vector_length;i++)
    {
        std::getline(read_file,line);//Read
        v[i]=atof(line.c_str());
    }
    read_file.close();

    return v;
}
