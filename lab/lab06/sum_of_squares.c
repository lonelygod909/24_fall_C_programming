#include <stdio.h>
#include <math.h>
#include <assert.h>
/* Given a positive integer n, write n as a sum of k squares,
where k <= 4, that is, n = a1^2 + ... + ak^2, making k 
as small as possible.
*/
int is_square(int n){
  if (sqrt(n) == (int)sqrt(n) ){
    return (int)sqrt(n);
  }
  return 0;
}
int two_sum_of_squares(int n){
  for (int i = 1; i <= (int)sqrt(n / 2.0); i++){
      if (is_square(n - i * i)){
        return i;
      }
  }
  return 0;
}
int three_sum_of_squares(int n){
  for (int i = 1; i <= (int)sqrt(n / 3.0) ; i++){
    if (two_sum_of_squares(n - i * i)){
      return i;
    }
  }
  return 0;
}

void sum_of_squares(int n, int* k, int* list) {
  int s = is_square(n);
  if (s) {
    *k = 1;
    list[0] = s;
  }
  else if((s = two_sum_of_squares(n))){
    *k = 2;
    list[0] = s;
    list[1] = (int)sqrt(n - s * s);
  }
  else if ((s = three_sum_of_squares(n))){
    *k = 3;
    list[0] = s;
    list[1] = two_sum_of_squares(n - s * s);
    list[2] = (int)sqrt(n - s * s - list[1] * list[1]);
  }
  else{
    for (int i = 1; i <= (int)sqrt(n / 4.0); i++){
      if ((s = three_sum_of_squares(n - i * i))){
      *k = 4;
      list[0] = i;
      list[1] = s;
      list[2] = (int)sqrt(n - s * s - i * i);
      list[3] = (int)sqrt(n - s * s - i * i - list[2]*list[2]);
      int sumOfSquares = list[0]*list[0] + list[1]*list[1] + list[2]*list[2] + list[3]*list[3];
            if (sumOfSquares == n) {
                *k = 4;
                break; 
            }
      }
    }
  }
}
void TestCase1() {
  // Test Case 1: 99999
  int k ;
  int list[4] ;
  sum_of_squares(99999, &k, list);
  assert(k == 4);
  int sumOfSquares = 0;
  for(int i = 0; i < k ; i++){
    //printf("%d ", list[i]);
    sumOfSquares += list[i]*list[i];
  }
  //printf("%d", sumOfSquares);
  assert(sumOfSquares == 99999);
  printf("Passed TestCase1\n");
}

void TestCase2() {
  // Test Case 1: 87352
  int k ;
  int list[4] ;
  sum_of_squares(87352, &k, list);
  assert(k == 3);
  int sumOfSquares = 0;
  for(int i = 0; i < k ; i++){
    sumOfSquares += list[i]*list[i];
  }
  assert(sumOfSquares == 87352);
  printf("Passed TestCase2\n");
}

void TestCase3() {
  // Test Case 3: 57
  int k ;
  int list[4] ;
  sum_of_squares(57, &k, list);
  assert(k == 3);
  int sumOfSquares = 0;
  for(int i = 0; i < k ; i++){
    sumOfSquares += list[i]*list[i];
  }
  assert(sumOfSquares == 57);
  printf("Passed TestCase3\n");
}

int main() {
  TestCase1();
  TestCase2();
  TestCase3();
  return 0;
}