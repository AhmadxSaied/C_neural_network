#include <Matrices.h>
#include <stdlib.h>
typedef struct Layer
{
    int neurons_number;
    Matrix* weights;
    Matrix* biases;
    Matrix* activations;
    Matrix* dactivations;
    Matrix* z;
    Matrix* dweights;
    Matrix* dbiases;
    Matrix* delta;

    Matrix* (*activation_function)(Matrix* matrix);
    Matrix* (*dactivation_function)(Matrix* matrix);

} Layer;

Layer* create_Layer(int layer_neurons, int nextlayer_neurons,double(*activation_function)(double val),double(*dactivation_function)(double val)){

    Layer* layer = malloc(sizeof(layer));

    layer->weights = create_Matrix(nextlayer_neurons,layer_neurons);
    layer->dweights = create_Matrix(nextlayer_neurons,layer_neurons);
    layer->biases = create_Matrix(nextlayer_neurons,1);
    layer->biases = create_Matrix(nextlayer_neurons,1);
    layer->z = create_Matrix(nextlayer_neurons, 1);
    layer->activations = create_Matrix(nextlayer_neurons,1);
    layer->dactivations = create_Matrix(nextlayer_neurons,1);
    layer->activation_function = activation_function;
    layer->dactivation_function = dactivation_function;
    return layer;

}