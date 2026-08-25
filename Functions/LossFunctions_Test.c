#include <stdlib.h>
#include <stdio.h>
#include "LossFunctions.c"
int main(){
    int output[10][2] = {
        {1,2},
        {3,4},
        {5,4},
        {5,8},
        {8,6},
        {3,2},
        {5,4},
        {9,7},
        {25,20}
    };


    Matrix* out = create_Matrix(10,2);

    for(int i = 0 ;i < 10 ; i++){
        for(int j = 0 ; j < 2 ; j++){
            matrix_cell_set(output[i][j],i,j,out);
        }
    }

    int reference[10][2] = {
        {3,4},
        {5,4},
        {5,8},
        {8,6},
        {3,2},
        {5,4},
        {9,7},
        {25,20},
        {1,2},
    };

    Matrix* ref = create_Matrix(10,2);

    for(int i = 0 ;i < 10 ; i++){
        for(int j = 0 ; j < 2 ; j++){
            matrix_cell_set(reference[i][j],i,j,out);
        }
    }

    printf("%f",MSE(out,ref));
}