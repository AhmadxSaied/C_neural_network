#include <stdio.h>
#include <Model.h>
#include <ActivationFunctions.h>
#include <Initializations.h>
#include <Printing_Model.h>
int main(){

    int layers[] = {16,16,-1};

    Model* model = create_Model(784,2,layers,10,sigmoid,dsigmoid,dsigmoidMat,He_Initialization);


    print_Model(model);

    // printf("error %f\n",forward(input,model,ref));
}
