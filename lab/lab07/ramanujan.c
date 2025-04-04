#include <stdio.h>
#include <assert.h>
#include <math.h>
/*
Ramanujan number is the smallest positive integer, which can be
expressed as the sum of two cubic numbers in two different ways.
It is also known as the Hardy-Ramanujan number.

Find this number.
*/

// Return the Ramanujan number.
int is_cube(long long n) {
    if (n < 0) return 0; // 如果是负数，直接返回
    long long root = round(pow(n, 1.0 / 3));
    return root * root * root == n ? root : 0;
}

int sum_of_cubes(long long n) {
    int sum = 0;
    for (long long i = 0; i * i * i <= n / 2; i++) {
        long long remainder = n - i * i * i;
        if (is_cube(remainder)) {
            sum+=1; // 找到立方和
        }
    }
    return sum;
  }
int ramanujan() {
    long long i = 0;
    while (1) {
        int s = sum_of_cubes(i);
        if (s == 2) {
            return i;
            break;
        }
        i++;
    }
    return 0;
}

int main() {
  assert(ramanujan() == 1729);
  printf("Passed the test.\n");
  return 0;
}
