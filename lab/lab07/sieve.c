#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

/*
Use the Sieve of Eratosthenes to count the number of
primes between 1 and n.
*/

// Return the number of primes between [2, n], where
// n <= 10^8.
int count_primes(int n) {
  int* array = (int*) malloc((n - 1) * sizeof(int));
  for (int i = 0; i < n - 1; i++){
    array[i] = 1;
  }
  int i = 0;
  int cnt = 0;
  while ((i + 2) * (i + 2) <= n)
  {
    if (array[i]){
      for (int j = 0; (i + 2) * (i + 2) + j * (i + 2) <= n ; j++){
        array[(i + 2) * (i + 2) + j * (i + 2) - 2] = 0;
      }
    }
    i++;
  }
  for (int i = 0; i < n - 1; i++){
    cnt += array[i];
  }
  return cnt;
  
  
}
void TestCase1() {
  // Test Case 1: n:10000 result=1229
  int res;
  res=count_primes(10000);
  assert(res==1229);
  printf("Passed TestCase1\n");
}

void TestCase2() {
  // Test Case 2: n=99988865 result=5760854
  int res;
  res=count_primes(99988865);
  assert(res==5760854);
  printf("Passed TestCase2\n");
}

void TestCase3() {
  // Test Case 3: n=100 result=25
  int res;
  res=count_primes(100);
  assert(res==25);
  printf("Passed TestCase3\n");
}
int main() {
  TestCase1();
  TestCase2();
  TestCase3();
  return 0;
}
