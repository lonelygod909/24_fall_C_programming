#include <stdio.h>
#include <assert.h>

typedef void (*fun_t)(double*, double*);

// Swap two doubles
void swap(double *x, double *y) {
  double temp;
  temp=*x;
  *x=*y;
  *y=temp;
}

void TestSwapCase1(fun_t swap) {
  double x = 1.00;
  double y = 1.00;
  swap(&x, &y);
  assert(x == 1.00);
  assert(y == 1.00);
  printf("Passed %s\n", __func__);
}

void TestSwapCase2(fun_t swap) {
  double x = 1.00;
  double y = 2.00;
  swap(&x, &y);
  assert(x == 2.00);
  assert(y == 1.00);
  printf("Passed %s\n", __func__);
}

int main() {
  TestSwapCase1(swap);
  TestSwapCase2(swap);
  return 0;
}
