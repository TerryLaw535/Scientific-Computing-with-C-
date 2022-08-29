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
csr_matrix csrformat_dissym();
csr_matrix csrformat_sym();
double* Ax_csr(csr_matrix A,double* x);
void Decsrmatrix(csr_matrix& A);
double* read_vector(std::string file);
csr_matrix read_csrmatrix(std::string file);
