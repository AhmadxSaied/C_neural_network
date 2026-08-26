#ifndef LAYER_H
#define LAYER_H
#include <Matrices.h>
#include <stdio.h>
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

    Matrix* (*Mat_dactivation_function)(Matrix* matrix);
    double(*activation_function)(double val);
    double(*dactivation_function)(double val);
    void (*initializationFunction)(int input,int output,Matrix* matrix);

} Layer;


Layer* create_Layer(int layer_neurons, int nextlayer_neurons,double(*activation_function)(double val),double(*dactivation_function)(double val),
Matrix* (*Mat_dactivation_function)(Matrix* matrix),void (*initializationFunction)(int input,int output,Matrix* matrix)
);

#endif