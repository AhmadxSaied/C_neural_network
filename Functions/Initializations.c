#include <Initializations.h>

void xavier_Initialization(int input,int output,Matrix* matrix){

    srand(time(NULL));
    assert(matrix != NULL && input > 0 && output > 0);

    double lower = (double)(-sqrt(6.0)) / (double)(sqrt(input + output));
    double upper = -lower;
    for(int i = 0 ; i < matrix->rows ; i++){
        for(int j = 0 ; j < matrix->cols ; j++){

            double ran = ((double)rand()) / (double)RAND_MAX;
            
            ran = ran*(upper - lower) + lower;

            matrix_cell_set(ran,i,j,matrix);
        }
    }
}

void He_Initialization(int input,int output,Matrix* matrix){
    srand(time(NULL));
    assert(matrix != NULL && input > 0 && output > 0);
    
    double std = (double)(sqrt(2)) / (double)input;
    for(int i = 0 ; i < matrix->rows ; i++){
        for(int j = 0 ; j < matrix->cols ; j++){

            double ran = ((double)rand()) / (double)RAND_MAX;
            
            ran = ran*std;

            matrix_cell_set(ran,i,j,matrix);
        }
    }
}