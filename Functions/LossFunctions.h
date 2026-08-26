#ifndef LOSSFUNCTION_H
#define LOSSFUNCTION_H

#include <Matrices.h>
#include <math.h>

double MSE(Matrix* output,Matrix* reference);
Matrix* dMSE(Matrix* output,Matrix* reference);

#endif