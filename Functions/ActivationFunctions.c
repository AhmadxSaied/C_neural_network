#include <ActivationFunctions.h>

double sigmoid(double val) {
    const double euler = exp(1);
    return (1 /  (1 + pow(euler,-val)));
}
double dsigmoid(double val){
    double sigval = sigmoid(val);
    return sigval * (1-sigval);
}

double relu(double val){
    return ((val >=0) ? val : 0);
}

double drelu(double val){
    return ((val > 0)? 1 : 0);
}

Matrix* dreluMat(Matrix* matrix){

    assert(matrix != NULL);

    Matrix* result = create_Matrix(matrix->rows,
        matrix->cols
    );

    for(int i = 0 ; i < matrix->rows ; i++){
        for(int j = 0 ; j < matrix->cols ; j++){
            double cellvall = matrix_cell_get(i,j,matrix);
            
            double postactder = drelu(cellvall);

            matrix_cell_set(postactder,i,j,result);

        }
    }
    return result;
}

Matrix* dsigmoidMat(Matrix* matrix){

    assert(matrix != NULL);

    Matrix* result = create_Matrix(matrix->rows,
        matrix->cols
    );

    for(int i = 0 ; i < matrix->rows ; i++){
        for(int j = 0 ; j < matrix->cols ; j++){
            double cellvall = matrix_cell_get(i,j,matrix);
            
            double postactder = dsigmoid(cellvall);

            matrix_cell_set(postactder,i,j,result);

        }
    }
    return result;
}