#ifndef MATRICES_H
#define MATRICES_H

typedef struct Matrix
{
    int rows;
    int cols;
    double* data;
} Matrix;

Matrix* create_Matrix(int rows,int cols);
Matrix* matrix_dot(Matrix* matrix_A,Matrix* matrix_B);
Matrix* matrix_add(Matrix* matrix_A,Matrix* matrix_B);
Matrix* matrix_add_1D_to_2D(Matrix* matrix_A,Matrix* matrix_B);
int matrix_cell_set(double value,int i,int j,Matrix* matrix);
double matrix_cell_get(int i,int j,Matrix* matrix);
void free_matrix(Matrix* matrix);
#endif