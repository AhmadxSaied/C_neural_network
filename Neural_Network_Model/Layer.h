#ifndef LAYER_H
#define LAYER_H
#include <Matrices.h>

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
    void (*initializationFunction)(Matrix* matrix);

} Layer;


Layer* create_Layer(int layer_neurons, int nextlayer_neurons,double(*activation_function)(double val),double(*dactivation_function)(double val),
void (*initializationFunction)(Matrix* matrix)
);

#endif