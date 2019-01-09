#include <iostream>
#include <cmath>

using namespace std;
double EPSILON = 0.01;

void sintetic( double *array, double *array1, int size, double r, double s ) {
    array[size-1] = array1[size-1];
    array[size-2] = array[size-1] * r + array1[size-2];

    for ( int i = size - 3; i >= 0; i-- ) {
        array[i] = ( array[i + 1] * r ) + ( array[i + 2] * s ) + array1[i];
    }
    return;
}

void bairstow(double* array, double r, double s){
  double arrayValue[] = {1.25, -3.875, 2.125, 2.75, -3.5, 1};
  int size = sizeof(arrayValue) / sizeof(arrayValue[0]);
  int counter = 1;
  double arrayB[size];
  double arrayC[size];
  double dr, ds;

  do {
      sintetic( arrayB, arrayValue, size, r, s );
      sintetic( arrayC, arrayB, size, r, s );
      //Using Cramer we get delta r and delta s
      dr = ( -arrayB[1] * arrayC[2] - arrayC[3] * -arrayB[0] ) / ( arrayC[2] * arrayC[2] - arrayC[1] * arrayC[3] );
      ds = ( -arrayB[0] * arrayC[2] - arrayC[1] * -arrayB[1] ) / ( arrayC[2] * arrayC[2] - arrayC[1] * arrayC[3] );

      double errorR = ( dr / r ) * 100;
      double errorS = ( ds / s ) * 100;

      if ( abs(errorR) <= EPSILON && abs(errorS) <= EPSILON ) {
          break;
      }
      r += dr;
      s += ds;
      counter++;
  } while (true);

  double x1 = ( r + sqrt( r * r + 4 * s ) ) / 2;
  double x2 = ( r - sqrt( r * r + 4 * s ) ) / 2;

  cout << "Roots: " << x1 << ", " << x2 << endl;

  cout << "Coeficientes de la funcion restantes: " << endl;
  for ( int i = 0; i < size; i++ ) {
      cout << arrayC[i] << ", ";
  }
  cout << endl;
}

int main() {
    
    double r;
    double s;
    int size;
    cout << "De que grado sera el polinomio?" << endl;
    cin >> size;

    size++;

    cout << "r" << endl;
    cin >> r;

    cout << "s" << endl;
    cin >> s;

    double arrayValue[size];

    cout << "Ingrese los coeficientes del polinomio del menor a mayor grado" << endl;
    for (int i = 0; i < size; i++) {
      cin >> arrayValue[i];
    }
    bairstow(arrayValue, r, s);
    return 0;
}
