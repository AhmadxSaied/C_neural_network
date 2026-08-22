#include "Matrices.h"
#include <stdio.h>
#include <assert.h>
int main(){

    int mat[2][3] = {{1,2,3},{2,5,6}};
    int mat2[3][2] = {{1,2},{2,5},{8,7}};

    int matres[2][2] = {{29,33},{60,71}};

    Matrix* matrixa = create_Matrix(2,3);
    Matrix* matrixb = create_Matrix(3,2);

    for(int i = 0 ;  i < 2 ; i++){
        for(int j = 0 ; j < 3 ; j++){
            matrix_cell_set(mat[i][j],i,j,matrixa);
        }
    }

    for(int i = 0 ;  i < 3 ; i++){
        for(int j = 0 ; j < 2 ; j++){
            matrix_cell_set(mat2[i][j],i,j,matrixb);
        }
    }

    Matrix* res = matrix_dot(matrixa,matrixb);

    for(int i = 0 ; i < res->rows ; i++){
        for(int j = 0 ; j < res->cols;j++){
            assert(matrix_cell_get(i,j,res) == matres[i][j]);
        }
    }
    free_matrix(matrixa);
    free_matrix(matrixb);
    free_matrix(res);
    printf("==========================================\nTest 1 passed\n");

    int mat3[3][3] = {{1,2,3},{2,5,6},{8,7,9}};
    int mat4[3][3] = {{1,2,3},{2,5,6},{8,7,9}};

    int matres2[3][3] = {{2,4,6},{4,10,12},{16,14,18}};

    matrixa = create_Matrix(3,3);
    matrixb = create_Matrix(3,3);

    for(int i = 0 ;  i < 3 ; i++){
        for(int j = 0 ; j < 3 ; j++){
            matrix_cell_set(mat3[i][j],i,j,matrixa);
        }
    }

    for(int i = 0 ;  i < 3 ; i++){
        for(int j = 0 ; j < 3 ; j++){
            matrix_cell_set(mat4[i][j],i,j,matrixb);
        }
    }

    res = matrix_add(matrixa,matrixb);

    for(int i = 0 ; i < res->rows ; i++){
        for(int j = 0 ; j < res->cols;j++){
            assert(matrix_cell_get(i,j,res) == matres2[i][j]);
        }
    }
    printf("==========================================\nTest 2 passed\n");
    return 0;
}