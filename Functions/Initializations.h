#ifndef INITIALIZATION_H
#define INITIALIZATION_H

#include <stdlib.h>
#include <Matrices.h>
#include <assert.h>
#include <math.h>
#include <time.h>
void xavier_Initialization(int input, int output, Matrix *matrix);
void He_Initialization(int input, int output, Matrix *matrix);

#endif