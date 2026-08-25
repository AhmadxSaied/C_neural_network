#include <stdlib.h>
#include <Matrices.h>
#include <string.h>
#include <assert.h>
#include "Layer.c"
#include "LossFunctions.c"
typedef struct Model
{
    int input_size;
    int number_of_hidden_layers;
    int* layer_sizes;
    int output_size;

    Layer* layers;

}Model;


Model* create_Model(int input_size,int number_of_hidden_layers,int* layer_sizes,int output_size,
    double(*activation_function)(double val),double(*dactivation_function)(double val)
){

    assert(number_of_hidden_layers > 0);
    
    size_t length = 0;
    
    while(layer_sizes[length] != -1)length++;

    assert(length == number_of_hidden_layers);


    Layer* layers = malloc(sizeof(Layer) * (1+number_of_hidden_layers));

    layers[0] = *create_Layer(input_size,layer_sizes[0],activation_function,dactivation_function);


    for(int i = 0 ; i < length -1; i++){
        layers[i+1] = *create_Layer(layer_sizes[i],layer_sizes[i+1],activation_function,dactivation_function);
    }

    layers[length] = *create_Layer(layer_sizes[length-1],output_size,activation_function,dactivation_function);

    Model* model = malloc(sizeof (Model));

    model->input_size=input_size;

    int* clayer_sizes = malloc(sizeof(int) * number_of_hidden_layers);

    memcpy(clayer_sizes,layer_sizes,sizeof(int) * number_of_hidden_layers);
    model->layer_sizes = clayer_sizes;
    model->number_of_hidden_layers = length;
    model->output_size = output_size;
    model->layers = layers;

    return model;
}


void forward(Matrix* input, Model* Model,Matrix* reference){


    Matrix* WxI = create_Matrix(Model->layers[0].weights->rows,input->cols);

    WxI = matrix_dot(Model->layers[0].weights,input);

    Model->layers[0].activations = (WxI,Model->layers[0].biases);

    matrix_apply_activation(Model->layers[0].activations,Model->layers[0].activation_function);

    free(WxI);
    for(int i = 1 ; i <= Model->number_of_hidden_layers ; i++){
        Matrix* WxI = create_Matrix(Model->layers[i].weights->rows,Model->layers[i-1].activations->cols);

        WxI = matrix_dot(Model->layers[i].weights,Model->layers[i-1].activations);
    
        Model->layers[i].activations = (WxI,Model->layers[i].biases);
    
        matrix_apply_activation(Model->layers[i].activations,Model->layers[i].activation_function);

        free(WxI);
    }

    double error = MSE(Model->layers[Model->number_of_hidden_layers].activations,reference);

    
}

void backward(Model* model,Matrix* reference){

    assert(model != NULL && reference != NULL);

    model->layers[model->number_of_hidden_layers].dactivations =
        dMSE(model->layers[model->number_of_hidden_layers].activations,reference);
        
    
}