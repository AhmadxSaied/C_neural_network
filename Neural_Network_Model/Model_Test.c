#include <stdio.h>
#include <Model.h>
#include <ActivationFunctions.h>
#include <Initializations.h>
#include <Printing_Model.h>
int main(){

    int layers[] = {1,2,-1};

    Model* model = create_Model(3,2,layers,2,sigmoid,dsigmoid,dsigmoidMat,He_Initialization);
    // print_Model(model);


    Matrix* input = create_Matrix(3,1);
    matrix_cell_set(1,0,0,input);
    matrix_cell_set(1,1,0,input);
    matrix_cell_set(1,2,0,input);

    Matrix* ref = create_Matrix(3,1);
    matrix_cell_set(5,0,0,ref);
    matrix_cell_set(2,1,0,ref);
    matrix_cell_set(2,2,0,ref);
    print_Model(model);

    printf("error %f\n",forward(input,model,ref));

    backward(input,model,ref,0.1);

    print_Model(model);

    // printf("error %f\n",forward(input,model,ref));
}
