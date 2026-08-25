#include <stdlib.h>
#include <Matrices.h>
#include <string.h>
#include <assert.h>
#include "Layer.c"
typedef struct Model
{
    int input_size;
    int number_of_hidden_layers;
    int* layer_sizes;
    int output_size;

    Layer* layers;

}Model;


Model* create_Model(int input_size,int number_of_hidden_layers,int* layer_sizes,int output_size){

    assert(number_of_hidden_layers > 0);
    
    size_t length = 0;
    
    while(layer_sizes[length] != -1)length++;

    assert(length == number_of_hidden_layers);


    Layer* layers = malloc(sizeof(Layer) * (1+number_of_hidden_layers));

    layers[0] = *create_Layer(input_size,layer_sizes[0]);


    for(int i = 0 ; i < length -1; i++){
        layers[i+1] = *create_Layer(layer_sizes[i],layer_sizes[i+1]);
    }

    layers[length] = *create_Layer(layer_sizes[length-1],output_size);

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