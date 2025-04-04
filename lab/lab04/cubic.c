#include <stdio.h>
#include <assert.h>
#include <math.h>

// Solve the cubic equation x^3 + c2*x^2 + c1*x + c0 = 0 with a given precision eps.
// The number of real solutions is stored in *cnt, where *cnt can be 1, 2, or 3.
// The solutions are stored in sol[0], ..., sol[*cnt - 1] and in ascending order.
void solve_cubic_equ(double c2, double c1, double c0, double eps, int* cnt, double* sol) {
    double a = - 100.0 * fmax(fmax(fabs(c2), fabs(c1)), fmax(fabs(c0), 1.0));
    double b = - a;
    double c = (a + b) / 2.0;
    while ((b - a) / 2 > eps){
        if (c*c*c + c2*c*c + c1*c + c0 == 0){
            break;
        }
        else if ((c*c*c + c2*c*c + c1*c + c0) * (a*a*a + c2*a*a + c1*a + c0) < 0){
            b = c;
        }
        else a = c;
        c = (a + b) / 2.0;
    }
    sol[0] = c;
    double prod = c == 0 ? c1 : - c0 / c;
    double sum = c == 0 ? -c2 : -c2 - c;
    double d = sum * sum - 4 * prod;
    if (d < -2 * eps) *cnt = 1;
    else if (d < 2 * eps){
      *cnt = 2; 
      sol[1] = sum / 2;
    }
    else {
      sol[0] = (sum - sqrt(d)) / 2;
      sol[1] = (sum + sqrt(d)) / 2; 
      *cnt = 3; 
      if (c > sol[1]) sol[2] =c;
      else {
        sol[2] = sol[1];
        sol[1] = sol[0];
        sol[0] = c;
      } 
    }

}

void TestCase1() {
  // Test Case 1: x^3 - 1 = 0, only one real root x = 1
  double eps = 1e-6;
  int cnt;
  double sol[3];
  solve_cubic_equ(0, 0, -1, eps, &cnt, sol);
  printf("Test Case 1: Expected 1 root, x = 1\n");
    printf("Number of roots: %d\n", cnt);
    for (int i = 0; i < cnt; i++) {
        printf("Root %d: %.6f\n", i + 1, sol[i]);
    }
    assert(cnt == 1 && fabs(sol[0] - 1) < eps);
    printf("Passed TestCase1\n");
}

void TestCase2() {
  // Test Case 2: (x - 1)^2(x + 2) = 0, two real roots x = 1 (double root), x = -2
  double eps = 1e-6;
  int cnt;
  double sol[3];
  solve_cubic_equ(0, -3, 2, eps, &cnt, sol);
  printf("Test Case 2: Expected 2 root, x = 1 (double), x = -2\n");
  printf("Number of roots: %d\n", cnt);
  for (int i = 0; i < cnt; i++) {
    printf("Root %d: %.6f\n", i + 1, sol[i]);
  }
  assert(cnt == 2 && fabs(sol[0] + 2) < eps && fabs(sol[1] - 1) < eps);
  printf("Passed TestCase2\n");

}

void TestCase3() {
  // Test Case 3: x^3 - 6x^2 + 11x - 6 = 0, three real roots x = 1, 2, 3
  double eps = 1e-6;
  int cnt;
  double sol[3];
  solve_cubic_equ(-6, 11, -6, eps, &cnt, sol);
  printf("Test Case 3: Expected 3 roots, x = 1, 2, 3\n");
  printf("Number of roots: %d\n", cnt);
  for (int i = 0; i < cnt; i++) {
    printf("Root %d: %.6f\n", i + 1, sol[i]);
  }
  assert(cnt == 3 && fabs(sol[0] - 1) < eps && fabs(sol[1] - 2) < eps && fabs(sol[2] - 3) < eps);
  printf("Passed TestCase3\n");
}

int main() {
  TestCase1();
  TestCase2();
  TestCase3();
  return 0;
}