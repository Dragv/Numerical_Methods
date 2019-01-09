#include <iostream>
#include <cmath>
#include <stdexcept>

#define ITER 1000
#define MINERR 1E-15

using namespace std;

typedef double (* vFunctionCall)(double x);

double abError(float x0, float x1){
  return x1-x0;
}

double reError(float x0, float x1){
  return (x1-x0)/x1;
}

double function1(double x) {
    return exp(x) - pow(x, 2) + 3 * x - 2;
}

double functionDerivative (double x){
    return exp(x) - 2*x + 3;
}

float tangenteMethod(vFunctionCall funct, vFunctionCall deri, float a){
    float x0 = a;
    float x1;
    float err;
    int i = 0;
    do{
        if (deri(x0) == 0){
            throw invalid_argument("Math error");
        }
        x1 = x0;
        x0 = x1 - (funct(x1)/deri(x1));
        err = abs(x0-x1);
        if (i > ITER){
            throw invalid_argument("Max number of iterations reached");
        }
        cout << "Iteracion " << i << ", Error absoluto iterativo " << abError(x0, a) << ", Error relativo iterativo " << reError(x0, a) << '\n';
        i++;
    } while (err >= MINERR);
    return x0;
}

int main() {
    float x0;
    cout << "x inicial" << '\n';
    cin >> x0;

    cout << tangenteMethod(function1, functionDerivative, x0) << endl;

    return 0;
}
