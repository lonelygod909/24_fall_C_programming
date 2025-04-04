#include <stdio.h>
#include <stdlib.h>
#include <time.h>
const double pi = 3.1415927;
double random_square(){
  return 2.0*((double)rand())/RAND_MAX-1.0;
}
/*
Sample a random point (x, y) in the square [-1, 1] * [-1, 1].
There is a unit circle C centered on (0, 0) with a radius of 1.
The probability that a randomly chosen point falls inside
the circle C is exactly PI / 4.

Estimate the value of PI with a precision of 1e-3 by sampling
a sufficient number of points.
*/
int main() {
  srand(time(0));
  double x,y;
  double est;
  double p=0;
  int sum=0,inc=0;
  while (est-pi>1e-3||est-pi<-1e-3){
    x=random_square();
    y=random_square();
    sum ++;
    if (x*x+y*y<=1) inc++;
    est=(double)inc/sum*4;
  }
  printf("%.3lf",est);
  return 0;
}