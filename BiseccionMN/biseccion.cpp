#include <iostream>
#include <cmath>

#define MAXI 1000
#define MIN 1E-10

using namespace std;

typedef double (* vFunctionCall)(double x);

double biseccion(vFunctionCall fun, double x0, double x1) {
  double y0 = fun(x0);
  double y1 = fun(x1);

  if ((y0 <= 0 && y1 <= 0) || (y0 >= 0 && y1 >= 0)) {
    throw invalid_argument("received f(x0) and f(x1) of same sign");
  }

  if (y0 == 0) {
    return x0;
  } else if (y1 == 0) {
    return x1;
  }

  int i = 0;
  double x, y;

  for (int i = 0; i < MAXI; i++){
    x = (x0 + x1) / 2;
    y = fun(x);

    if (abs(y) <= MIN) {
      return x;
    }

    if ((y <= 0 && y0 <= 0) || (y >= 0 && y0 >= 0)) {
      // go left
      x0 = x;
      y0 = y;
    } else {
      // go right
      x1 = x;
      y1 = y;
    }
  }
  return x;
}

double Funforfun(double x) {
  return sin(x) + 2*x - 1;
}

int main() {
  cout << biseccion((vFunctionCall)Funforfun, -10, 10) << endl;
  return 0;
}
