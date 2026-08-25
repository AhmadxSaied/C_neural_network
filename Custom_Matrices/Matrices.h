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
Matrix* matrix_transpose(Matrix* matrix);
Matrix* multiply_scalar(double scale,Matrix* matrix);
Matrix* matrix_hadamard_product(Matrix* matrix_A,Matrix* matrix_B);
void matrix_zero(Matrix* matrix);
void matrix_apply_activation(Matrix* matrix,double (*activation)(double val));
int matrix_cell_set(double value,int i,int j,Matrix* matrix);
double matrix_cell_get(int i,int j,Matrix* matrix);
void free_matrix(Matrix* matrix);
#endif