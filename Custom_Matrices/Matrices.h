#ifndef MATRICES_H
#define MATRICES_H
#include <stdlib.h>
#include <assert.h>
typedef struct Matrix
{
    int rows;
    int cols;
    double *data;
} Matrix;

Matrix *create_Matrix(int rows, int cols);
Matrix *matrix_dot(Matrix *matrix_A, Matrix *matrix_B);
Matrix *matrix_add(Matrix *matrix_A, Matrix *matrix_B);
Matrix *matrix_add_1D_to_2D(Matrix *matrix_A, Matrix *matrix_B);
Matrix *matrix_transpose(Matrix *matrix);
Matrix *matrix_multiply_scalar(double scale, Matrix *matrix);
Matrix *matrix_hadamard_product(Matrix *matrix_A, Matrix *matrix_B);
Matrix *matrix_sum_axis(Matrix *matrix, int batch_size);
Matrix *get_output(Matrix *input, int *indices, int batch_size);
Matrix *get_input(Matrix *input, int *indices, int batch_size);
int matrix_cell_set(double value, int i, int j, Matrix *matrix);
double matrix_cell_get(int i, int j, Matrix *matrix);
int *argmax(Matrix *matrix);
void matrix_zero(Matrix *matrix);
void matrix_apply_activation(Matrix *result_Matrix, Matrix *matrix, double (*activation)(double val));
void free_matrix(Matrix *matrix);
void shuffle_columns(Matrix *input, Matrix *labels);
void swap_columns(Matrix *matrix, int col1, int col2);
#endif