#include "Matrices.h"
#include <stdlib.h>
#include <assert.h>

Matrix* create_Matrix(int rows,int cols){

    assert(rows >0 && cols > 0);

    Matrix* matrix = malloc(sizeof(Matrix));

    matrix->rows = rows;
    matrix->cols = cols;

    size_t totalsize = (size_t)rows * cols;

    matrix->data = malloc((totalsize * sizeof(double)));

    for(int i = 0 ; i < rows * cols;i++){
        matrix->data[i] = 0;
    }

    return matrix;
}


Matrix* matrix_dot(Matrix* matrix_A,Matrix* matrix_B){
    if(matrix_A == NULL || matrix_B) return NULL;
    assert(matrix_A->cols == matrix_B->rows);
    
    Matrix* result_matrix = create_Matrix(matrix_A->rows,matrix_B->cols);


    for(int i =0 ;i < matrix_A->rows;i++){

        for(int j = 0 ; j < matrix_B->rows;j++){

            /// matrix_B->rows === matrix_A->cols
            int index_A = (i * matrix_A->cols) + j;

            for(int k = 0 ; k < matrix_B->cols;k++){

                int index_B = (j * matrix_B->cols) + k;

                int result_index = (i*matrix_B->cols) + k;

                result_matrix->data[result_index] += matrix_A->data[index_A] * matrix_B->data[index_B];
            }
        }
    }
    return result_matrix;
}

Matrix* matrix_add(Matrix* matrix_A,Matrix* matrix_B){
    if(matrix_A == NULL || matrix_B) return NULL;
    assert(matrix_A->cols == matrix_B->cols && matrix_A->rows == matrix_B->rows);

    Matrix* result_matrix = create_Matrix(matrix_A->cols,matrix_B->rows);


    for(int i = 0 ;i < matrix_A->rows; i++){
        for(int j = 0 ; j < matrix_A->cols;j++){
            int index = i * matrix_A->cols + j;
            result_matrix->data[index] =  matrix_A->data[index] + matrix_B->data[index];
        }
    }
    return result_matrix;
}

Matrix* matrix_add_1D_to_2D(Matrix* matrix_A,Matrix* matrix_B){
    if(matrix_A == NULL || matrix_B) return NULL;
    assert(matrix_A->rows == matrix_B->rows);

    Matrix* result_matrix = create_Matrix(matrix_A->cols,matrix_A->rows);

    for(int i = 0 ; i < matrix_A->rows ; i++){
        for(int j = 0 ; j <matrix_A->cols;j++){
            int index_A = j + i* matrix_A->cols;
            result_matrix->data[index_A] = matrix_A->data[index_A] + matrix_B->data[i];
        }
    }
    return result_matrix;
}

int matrix_cell_set(double value,int i,int j,Matrix* matrix){
    if(matrix == NULL) return -1;
    int index = i*matrix->cols + j;
    assert(index < matrix->rows * matrix->cols);

    matrix->data[index] = value;
    return 1;
}

double matrix_cell_get(int i,int j,Matrix* matrix){
    
    assert(matrix !=NULL);

    int index = i*matrix->cols + j;
    assert(index < matrix->rows * matrix->cols);

    return matrix->data[index];
}


Matrix* matrix_multiply_scalar(double scale,Matrix* matrix){
    if(matrix == NULL) return NULL;

    int rows = matrix->rows;
    int cols = matrix->cols;

    Matrix* res_matrix = create_Matrix(rows,cols);

    for(int i = 0; i < rows;i++){
        for(int j = 0 ; j < cols ; j++){
            int index = i * cols + j;

            res_matrix->data[index] = matrix->data[index] * scale;
        }
    }
    return res_matrix;
}

Matrix* matrix_transpose(Matrix* matrix){
    if(matrix == NULL)return NULL;

    int cols = matrix->cols;
    int rows = matrix->rows;

    Matrix* transposed_matrix = create_Matrix(cols,rows);

    for(int i = 0 ; i < cols;i++){
        for(int j = 0 ; j < rows; j++){
            int index_t = i* rows + j;

            int index_normal = j * cols + i;

            transposed_matrix->data[index_t] = matrix->data[index_normal];

        }
    }
    return transposed_matrix;
}

void matrix_zero(Matrix* matrix){
    assert(matrix != NULL);

    for(int i = 0 ; i < matrix->rows;i++){
        for(int j = 0 ; j < matrix->cols ; j++){
            matrix_cell_set(0,i,j,matrix);
        }
    }
}

void matrix_apply_activation(Matrix* result_Matrix,Matrix* matrix,double (*activation)(double val)){
    
    assert(matrix != NULL);

    for(int i = 0 ; i < matrix->rows ; i++){
        for(int j = 0 ; j < matrix->cols ; j++){
            
            int index = i * matrix->cols + j;

            result_Matrix->data[index] = activation(matrix->data[index]);
        }
    }
}

Matrix* matrix_hadamard_product(Matrix* matrix_A,Matrix* matrix_B){
    if(matrix_A == NULL || matrix_B == NULL) return NULL;
    assert(matrix_A->cols == matrix_B->cols && matrix_A->rows == matrix_B->rows);

    Matrix* result_matrix = create_Matrix(matrix_A->rows,matrix_B->cols);


    for(int i = 0 ;i < matrix_A->rows; i++){
        for(int j = 0 ; j < matrix_A->cols;j++){
            int index = i * matrix_A->cols + j;
            result_matrix->data[index] =  matrix_A->data[index] * matrix_B->data[index];
        }
    }
    return result_matrix;
}


Matrix* matrix_sum_axis(Matrix* matrix){
    assert(matrix != NULL);

    Matrix* result_matrix = create_Matrix(matrix->rows,1);

    for(int i = 0 ; i< matrix->rows ; i++){
        result_matrix->data[i] = 0;
        for(int j = 0 ; j < matrix->cols ; j++){
            result_matrix->data[i] += matrix->data[i*matrix->cols + j];
        }
    }
    return result_matrix;
}

void free_matrix(Matrix* matrix){
    if(matrix == NULL)return;
    free(matrix->data);
    free(matrix);
    matrix = NULL;
}