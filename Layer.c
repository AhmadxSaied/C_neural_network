#include <Matrices.h>
#include <stdlib.h>
typedef struct Layer
{
    int neurons_number;
    Matrix* weights;
    Matrix* biases;
    Matrix* activations;
    Matrix* dweights;
    Matrix* dbiases;

    Matrix* (*activation_function)(Matrix* matrix);
    Matrix* (*dactivation_function)(Matrix* matrix);

} Layer;

Layer* create_Layer(int layer_neurons, int nextlayer_neurons){

    Layer* layer = malloc(sizeof(layer));

    layer->weights = create_Matrix(nextlayer_neurons,layer_neurons);
    layer->dweights = create_Matrix(nextlayer_neurons,layer_neurons);
    layer->biases = create_Matrix(nextlayer_neurons,1);
    layer->biases = create_Matrix(nextlayer_neurons,1);
    layer->activations = create_Matrix(nextlayer_neurons,1);

    // layer->activation_function = activationfunction;
    // layer->dactivation_function = dactivationfunction;
    return layer;

}