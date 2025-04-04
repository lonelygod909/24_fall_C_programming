#include <stdio.h>
#include <math.h>
const double pi = 3.1415927;
/*
Let zeta(s) = 1/1^s + 1/2^s + 1/3^s + ...
It is known that
  zeta(2) = PI^2 / 6
  zeta(4) = PI^4 / 90

The goal is to compute the constant PI to a precision of 1e-3
(meaning three decimal places) using the Riemann zeta function.
*/

int main() {
  long long n=1;
  double zeta=0;
  double est=0;
  while (est-pi<-1e-3 || est - pi>1e-3 ){
    zeta += 1.0/(n*n);
    est = sqrt(6*zeta);
    n++;
  }
  printf("%.3lf",est);
  return 0;
}