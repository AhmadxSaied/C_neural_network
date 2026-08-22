#include <stdlib.h>
#include <assert.h>
typedef struct Matrix
{
    int rows;
    int cols;
    double* data;
} Matrix;



Matrix* create_Matrix(int rows,int cols){
    Matrix* matrix = malloc(sizeof(Matrix));

    matrix->rows = rows;
    matrix->cols = cols;

    matrix->data = malloc(rows * cols * sizeof(double));
    for(int i = 0 ; i < rows * cols;i++){
        matrix->data[i] = 0;
    }

    return matrix;
}


Matrix* matrix_dot(Matrix* matrix_A,Matrix* matrix_B){

    assert(matrix_A->cols == matrix_B->rows);
    
    Matrix* result_matrix = create_Matrix(matrix_A->rows,matrix_B->cols);


    for(int i =0 ;i < matrix_A->rows;i++){
        for(int j = 0 ; j < matrix_A->cols;j++){
            for(int k = 0 ; k < matrix_B->rows;k++){
                int index_A = (i * matrix_A->cols) + k;

                int index_B = (k * matrix_B->cols) + j;

                result_matrix->data[index_A] = matrix_A->data[index_A] * matrix_B->data[index_B];
            }
        }
    }
    return result_matrix;
}

Matrix* matrix_add(Matrix* matrix_A,Matrix* matrix_B){
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