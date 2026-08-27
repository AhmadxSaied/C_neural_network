#ifndef LOADER_H
#define LOADER_H

#include <stdlib.h>
#include <stdio.h>
#include <Matrices.h>
#include <Printing_Model.h>

typedef struct Loader{
    char* test_URL;
    char* test_label_URL;
    char* train_URL;
    char* train_label_URL;
}Loader;

Loader* create_Loader(char* test_URL,char* test_label_URL,char* train_URL,char* train_label_URL);
Matrix* load_train_samples(Loader* loader,int input_size,int samples);
Matrix* load_test_samples(Loader* loader,int input_size,int samples);
Matrix* load_training_labels(Loader* loader,int samples);
Matrix* load_test_labels(Loader* loader,int samples);
#endif