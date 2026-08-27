#include <Layer.h>


Layer* create_Layer(int layer_neurons, int nextlayer_neurons,double(*activation_function)(double val),double(*dactivation_function)(double val),
Matrix* (*Mat_dactivation_function)(Matrix* matrix),void (*initializationFunction)(int input,int output,Matrix* matrix)
){

    Layer* layer = malloc(sizeof(Layer));

    // printf("create_Layer called: rows=%d cols=%d\n", nextlayer_neurons, layer_neurons); // or whatever your actual param names/order are

    layer->weights = create_Matrix(nextlayer_neurons,layer_neurons);
    layer->dweights = create_Matrix(nextlayer_neurons,layer_neurons);
    layer->biases = create_Matrix(nextlayer_neurons,1);
    layer->dbiases = create_Matrix(nextlayer_neurons,1);
    layer->z = create_Matrix(nextlayer_neurons, 1);
    layer->activations = create_Matrix(nextlayer_neurons,1);
    layer->dactivations = create_Matrix(nextlayer_neurons,1);
    layer->activation_function = activation_function;
    layer->dactivation_function = dactivation_function;
    layer->Mat_dactivation_function = Mat_dactivation_function;

    layer->initializationFunction = initializationFunction;
    layer->initializationFunction(layer_neurons,nextlayer_neurons,layer->weights);

    return layer;

}
void free_Layer_contents(Layer* layer){
    if(layer == NULL) return;
    free_matrix(layer->weights);
    free_matrix(layer->biases);
    free_matrix(layer->z);
    free_matrix(layer->activations);
    free_matrix(layer->dweights);
    free_matrix(layer->dbiases);
    free_matrix(layer->dactivations);
    free_matrix(layer->delta);
}