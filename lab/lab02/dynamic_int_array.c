#include <stdio.h>
#include <stdlib.h>

int main() {
  const long long n = 1000000000;
  int*p = (int*)malloc(n*sizeof(int));
  // 1. Dynamically create an int type array of length n, where
  //    n = 1000 000 000.
  // 2. Set all elements of the array to the constant 1.
  // 3. Free the array at the end.
  for (int i; i< n ; i++)
  p[i]=1;
  printf("Success!\n");
  free(p);
  return 0;
}