#ifndef MODEL_H
#define MODEL_H

#include <stdlib.h>
#include <stdio.h>
#include <Matrices.h>
#include <string.h>
#include <assert.h>
#include <Layer.h>
#include <LossFunctions.h>

typedef struct Model
{
    int input_size;
    int number_of_hidden_layers;
    int* layer_sizes;
    int output_size;

    Layer* layers;

}Model;

double forward(Matrix* input, Model* Model,Matrix* reference);
Model* create_Model(int input_size,int number_of_hidden_layers,int* layer_sizes,int output_size,
    double(*activation_function)(double val),double(*dactivation_function)(double val),
    void (*initializationFunction)(Matrix* matrix)
);
void backward(Matrix* input,Model* model,Matrix* reference,double learning_rate);
void step(Matrix* deltai_plus_1,Matrix* weight_i_plus_1,Matrix* prev_activations,Layer* layer,double learning_rate);

#endif