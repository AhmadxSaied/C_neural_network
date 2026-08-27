#ifndef TRAINER_H
#define TRAINER_H
#include <Printing_Model.h>
#include <Model.h>
#include <Loader.h>
#include <Matrices.h>

typedef struct trainer {
    Model* model;
    Matrix* input_data;
    Matrix* input_target;
    Matrix* output_data;
    Matrix* output_target;
    int epochs;
    Loader* loader;
    double learning_weight;
} Trainer;

Trainer* create_trainer(Model* model,Loader* loader,int epochs,int input_size,int samples,double learning_weight);
void Train(Trainer* trainer,int samples);
void free_Trainer(Trainer* trainer);
#endif