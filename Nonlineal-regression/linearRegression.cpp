#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

double fe(double alpha, double beta, double x){
  return alpha*exp(beta*x);
}

double fp(double alpha, double beta, double x){
  return alpha*pow(x, beta);
}

int main(){
  double n;
  double sum_x, sum_y, sum_square_x, sum_prod, av_x, av_y, a0, a1, alpha = 0, beta = 0;
  cout << "Enter value of n: ";
  cin >> n;

  bool potencia, exponencial;

  cout << "Modelo de potencia?: ";
  cin >> potencia;
  cout << "Modelo exponencial?: ";
  cin >> exponencial;

  ifstream inx("x.txt");
  ifstream iny("y.txt");

  if(!inx || !iny){
    cout << "Error" << endl;
  }
  cout << "\n  x\t  y" << endl;
  for(int i = 0; inx && iny && i < n; i++){
    double x, y;
    inx >> x;
    iny >> y;
    if(potencia){
      y = log10(y);
      x = log10(x);
    }
    else if(exponencial){
      y = log(y);
    }

    sum_x += x;
    sum_y += y;
    sum_square_x += x*x;
    sum_prod += x*y;

    cout << x << "\t" << y << endl;
  }

  inx.close();
  iny.close();

  av_x = sum_x / n;
  av_y = sum_y / n;

  a1 = (n*sum_prod - sum_x*sum_y)/(n*sum_square_x - sum_x*sum_x);
  a0 = (av_y - a1*av_x);

  if(potencia){
    alpha = pow(10,a0);
    beta = a1;
  }
  else if(exponencial){
    alpha = exp(a0);
    beta = a1;
  }
  double y_medida, y_calculada, x_medida, sr, st;

  ifstream iny2("y.txt");
  ifstream inx2("x.txt");
  for(int i = 0; i < n; i++){
    iny2 >> y_medida;
    inx2 >> x_medida;
    if(potencia){
      y_calculada = fp(alpha, beta, x_medida);
    }
    else if(exponencial){
      y_calculada = fe(alpha, beta, x_medida);
    }
    else{
      y_calculada = a0 + a1*x_medida;
    }
    sr += pow((y_medida - y_calculada),2);
    st += pow(y_medida-(av_y),2);
  }

  inx2.close();
  iny2.close();

  double ErrEstandar = sqrt(sr/(n-2));
  double r = sqrt((st-sr)/st);

  cout << "\nSum x: " << sum_x << " | Sum y: " << sum_y << " | Sum square x: " << sum_square_x << " | Sum product x*y: " << sum_prod << endl;
  cout << "\na1 = " << a1 << " | a0 = " << a0 << "\n" << endl;
  if(potencia){
    cout << "Alpha: " << alpha << " | Beta: " << beta << endl;
    cout << "y = " << alpha << " * x^(" << beta << ")\n" << endl;
  }
  else if(exponencial){
    cout << "Alpha: " << alpha << " | Beta: " << beta << endl;
    cout << "y = " << alpha << " * e^(" << beta << "*x)\n" << endl;
  }
  else{
    cout << "y = " << a0 << " + " << a1 << "x\n" << endl;
  }
  cout << "Error estandar de la estimación: " <<  ErrEstandar << endl;
  cout << "Coeficiente de determinacion: " << r << endl;
  cout << "Coeficiente de correlación: " << sqrt(r) << endl;

  return 0;
}
