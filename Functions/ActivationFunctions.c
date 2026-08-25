#include <assert.h>
#include <math.h>

double sigmoid(double val) {
    const double euler = exp(1);
    return (1 /  (1 + pow(euler,-val)));
}
double dsigmoid(double val){
    double sigval = sigmoid(val);
    return sigval * (1-sigval);
}

double relu(double val){
    return ((val >=0) ? val : 0);
}

double drelu(double val){
    return ((val > 0)? 1 : 0);
}