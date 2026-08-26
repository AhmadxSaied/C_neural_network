#include <LossFunctions.h>

double MSE(Matrix* output,Matrix* reference){
    double mse = 0;
    for(int i = 0 ; i < output->cols ; i++){
        double col_se = 0;

        for(int j = 0 ; j < output->rows ; j++){
            int index = j * output->cols + i;

            double se = output->data[index] - reference->data[index];
            se *= se;
            col_se += se;
        }   
        mse += (col_se / output->rows);
}
mse /= output->cols;
return mse;
}

Matrix* dMSE(Matrix* output,Matrix* reference){
    
    Matrix* dmse = create_Matrix(output->rows,output->cols);

    for(int i = 0 ; i < output->cols ; i++){
        double col_se = 0;

        for(int j = 0 ; j < output->rows ; j++){
            int index = j * output->cols + i;

            double se = output->data[index] - reference->data[index];

            dmse->data[index] = se * (2.0/output->rows * output-> cols);
        }   
}
    return dmse;
}

