#include <Layer.h>


Layer* create_Layer(int layer_neurons, int nextlayer_neurons,double(*activation_function)(double val),double(*dactivation_function)(double val),
void (*initializationFunction)(Matrix* matrix)
){

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


    layer->initializationFunction = initializationFunction;
    layer->initializationFunction(layer->weights);

    return layer;

}