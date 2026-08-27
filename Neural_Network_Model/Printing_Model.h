#ifndef PRINTING_MODEL_H
#define PRINTING_MODEL_H
#include <stdio.h>
#include "Matrices.h"
#include <Layer.h>
#include <Model.h>

void print_Matrix(Matrix* matrix, const char* label);
void print_Layer(Layer* layer, int layer_index);
void print_Model(Model* model);

#endif