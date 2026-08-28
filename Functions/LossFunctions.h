#ifndef LOSSFUNCTION_H
#define LOSSFUNCTION_H

#include <Matrices.h>
#include <math.h>
#define MSE_FLAG 0
#define CE_FLAG 1
double MSE(Matrix *output, Matrix *reference);
Matrix *dMSE(Matrix *output, Matrix *reference);
double CrossEntropy(Matrix *output, Matrix *reference);
Matrix *dCrossEntropy(Matrix *output, Matrix *reference);
#endif