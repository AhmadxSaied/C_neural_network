#ifndef ACTIVATIONFUNCTIONS_H
#define ACTIVATIONFUNCTIONS_H

#include <assert.h>
#include <math.h>
#include <Matrices.h>
#include <stdlib.h>

double sigmoid(double val);
double dsigmoid(double val);
double relu(double val);
double drelu(double val);
Matrix* dreluMat(Matrix* matrix);
Matrix* dsigmoidMat(Matrix* matrix);

#endif