#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <stdlib.h>
#define div divison

// Represent a complex number x + yi.
struct complex_number {
  double x;
  double y;
};

//Make a complex number.
struct complex_number make_complex_number(double a, double b){
  struct complex_number res;
  res.x = a;
  res.y = b;
  return res;
}

// Returns a + b.
struct complex_number add(struct complex_number a, struct complex_number b) {
  return make_complex_number(a.x + b.x, a.y + b.y);
}

// Returns a - b.
struct complex_number minus(struct complex_number a, struct complex_number b) {
  return make_complex_number(a.x - b.x, a.y - b.y);
}
// Returns a * b.
struct complex_number mult(struct complex_number a, struct complex_number b) {
  return make_complex_number(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x);
}

// Returns a / b, assuming b != 0.
// If b = 0, print an error message and return (0, 0).
struct complex_number div(struct complex_number a, struct complex_number b) {
  struct complex_number res;
  if (b.x == 0 && b.y == 0){
    printf("Division error!\n");
    return make_complex_number(0, 0);
  }
  return make_complex_number((a.x * b.x + a.y * b.y) / (b.x * b.x + b.y * b.y),
    (b.x * a.y - b.y * a.x) / (b.x * b.x + b.y * b.y));
}

// Returns the absolute value (or modulus) of a = x + yi, which is
// sqrt(x^2 + y^2). 
double modulus(struct complex_number a) {
  return sqrt(a.x * a.x + a.y * a.y);
}

// Returns the square root of a.
void square_root(struct complex_number a,struct complex_number* x_1, struct complex_number* x_2) {
  x_1 -> x = sqrt((a.x + sqrt(a.x * a.x + a.y * a.y)) / 2);
  *x_1 = make_complex_number(x_1 -> x, x_1 -> x != 0 ? a.y / (2 * x_1 -> x) : sqrt(-a.x));
  *x_2 = make_complex_number(- x_1 -> x, - x_1 -> y);
}

// Returns a^n.
struct complex_number power(struct complex_number a, int n) {
  struct complex_number one = {1, 0};
  if (n < 0) return div(one, power(a, -n));
  if (n == 0) return one;
  if (n % 2 == 1) 
    return mult(a, mult(power(a, n / 2), power(a, n / 2)));
  if (n % 2 ==0)
    return mult(power(a, n / 2), power(a , n / 2));
  return one;
}

// Compute the two roots of quadratic equation ax^2 + bx + c = 0.
// Let |x_1| <= |x_2|.
void sort_two_root(struct complex_number* x_1, struct complex_number* x_2){
  if (modulus(*x_1) > modulus(*x_2)){
    struct complex_number* temp = x_1;
    x_1 = x_2;
    x_2 = temp;
  }
}

void solve_quadratic(struct complex_number a, struct complex_number b, struct complex_number c,
  struct complex_number* x_1, struct complex_number* x_2) {
  struct complex_number* delta_1 = 
  (struct complex_number*)malloc(sizeof (struct complex_number));
  struct complex_number* delta_2 =
  (struct complex_number*)malloc(sizeof (struct complex_number));
  square_root(minus(power(b, 2), 
      mult(a, mult(c,(make_complex_number(4, 0))))),
    delta_1, delta_2);
  *x_1 = div(add(mult(make_complex_number(-1, 0), b),
      *delta_1),
    mult(make_complex_number(2, 0), a));
  *x_2 = div(add(mult(make_complex_number(-1, 0), b),
      *delta_2),
    mult(make_complex_number(2, 0), a));
  free (delta_1);
  free (delta_2);
  sort_two_root(x_1, x_2);
}

// Compare whether two complex numbers are equal (considering floating-point errors)
int complex_equal(struct complex_number a, struct complex_number b, double epsilon) {
  return (fabs(a.x - b.x) < epsilon) && (fabs(a.y - b.y) < epsilon);
}

// defined a small epsilon value for floating-point comparisons
const double EPSILON = 1e-6;

void TestAdd(){
  // test 1：add
  struct complex_number a = {1.0, 2.0};
  struct complex_number b = {3.0, 4.0};
  struct complex_number expected = {4.0, 6.0};
  struct complex_number result = add(a, b);
  assert(complex_equal(result, expected, EPSILON));

  printf("TestCase add passed!\n");
}

void TestMinus(){
  // test 2：minus
  struct complex_number a = {5.0, 6.0};
  struct complex_number b = {3.0, 4.0};
  struct complex_number expected = {2.0, 2.0};
  struct complex_number result = minus(a, b);
  assert(complex_equal(result, expected, EPSILON));

  printf("TestCase minus passed!\n");
}

void TestMult(){
  // test 3：mult
  struct complex_number a = {1.0, 2.0};
  struct complex_number b = {3.0, 4.0};
  struct complex_number expected = {-5.0, 10.0};
  struct complex_number result = mult(a, b);
  assert(complex_equal(result, expected, EPSILON));

  printf("TestCase mult passed!\n");
}

void TestDiv(){
  // test 4：div
  struct complex_number a = {1.0, 2.0};
  struct complex_number b = {3.0, 4.0};
  struct complex_number expected = {0.44, 0.08}; // 近似值
  struct complex_number result = div(a, b);
  assert(complex_equal(result, expected, 0.1)); // 使用较大的epsilon

  printf("TestCase div passed!\n");
}

void TestModulus(){
  // test 5：modulus
  struct complex_number a = {3.0, 4.0};
  double expected = 5.0;
  double result = modulus(a);
  assert(result == expected);

  printf("TestCase modulus passed!\n");
}

void TestSquareRoot1(){
  // test 6：square_root
  struct complex_number a = {3.0, 4.0};
  struct complex_number x_1 = {0.0, 0.0};
  struct complex_number x_2 = {0.0, 0.0};
  square_root(a,&x_1,&x_2);

  // (2 + 1i)^2 = 3 + 4i
  struct complex_number expectedx_1 = {2.0, 1.0};
  struct complex_number expectedx_2 = {-2.0, -1.0};
  assert(complex_equal(x_1, expectedx_1, EPSILON) && complex_equal(x_2, expectedx_2, EPSILON) ||
         complex_equal(x_1, expectedx_2, EPSILON) && complex_equal(x_2, expectedx_1, EPSILON));
  printf("TestCase square_root passed!\n");
}

void TestSquareRoot2(){
  // test 7：square_root
  struct complex_number a = {-4.0, 0.0};
  struct complex_number x_1 = {0.0, 0.0};
  struct complex_number x_2 = {0.0, 0.0};
  square_root(a,&x_1,&x_2);

  // sqrt(-4) = 0 + 2i 或 0 - 2i
  // 根据实现，应该返回x_1 = 0 + 2i , x_2 = 0 - 2i
  struct complex_number expectedx_1 = {0.0, 2.0};
  struct complex_number expectedx_2 = {0.0, -2.0};
  assert(complex_equal(x_1, expectedx_1, EPSILON) && complex_equal(x_2, expectedx_2, EPSILON));
  printf("TestCase square_root passed!\n");
}

void TestPower1(){
  // test 8：power
  struct complex_number a = {1.0, 1.0};
  int n = 3;
  struct complex_number expected = {-2.0, 2.0}; // (1+i)^3 = -2 + 2i
  struct complex_number result = power(a, n);
  assert(complex_equal(result, expected, EPSILON));

  printf("TestCase power passed!\n");  
}

void TestPower2(){
  // test 9：power
  struct complex_number a = {5.0, -3.0};
  int n = 0;
  struct complex_number expected = {1.0, 0.0};
  struct complex_number result = power(a, n);
  assert(complex_equal(result, expected, EPSILON));

  printf("TestCase power passed!\n");
}

void TestPower3() {
  // test 10：power
  struct complex_number a = {1.0, 1.0};
  int n = -1;
  struct complex_number expected = {0.5, -0.5}; // 1/(1+i) = (1 - i)/2
  struct complex_number result = power(a, n);
  //printf("the res is %lf + %lf i\n", result.x, result.y);
  assert(complex_equal(result, expected, EPSILON));

  printf("TestCase power passed!\n");  
}

void TestSolveQuadratic1() {
  // test 11：solve_quadratic
  // 方程 x^2 - 3x + 2 = 0，根为 x=1 和 x=2
  struct complex_number coef_a = {1.0, 0.0};
  struct complex_number coef_b = {-3.0, 0.0};
  struct complex_number coef_c = {2.0, 0.0};
  struct complex_number x1, x2;
  solve_quadratic(coef_a, coef_b, coef_c, &x1, &x2);
  struct complex_number expected1 = {1.0, 0.0};
  struct complex_number expected2 = {2.0, 0.0};
  assert(complex_equal(x1, expected1, EPSILON) && complex_equal(x2, expected2, EPSILON) ||
         complex_equal(x1, expected2, EPSILON) && complex_equal(x2, expected1, EPSILON));
  printf("TestCase solve_quadratic passed!\n");
}

void TestSolveQuadratic2() {
  // test 12：solve_quadratic
  // 方程 x^2 + (3+2i)x + (1-4i) = 0
  struct complex_number a = {1.0, 0.0};
  struct complex_number b = {3.0, 2.0};
  struct complex_number c = {1.0, -4.0};
  struct complex_number x1, x2;
  solve_quadratic(a, b, c, &x1, &x2);

  // 手动计算根：
  // 判别式 = (3+2i)^2 - 4*(1)*(1-4i) = 9 + 12i + 4i^2 - 4 + 16i = (9 - 4 - 4) + (12 + 16)i = 1 + 28i
  // sqrt(1 + 28i) ≈ 5.2915 + 2.3670i （近似值）
  // 根 = [-(3+2i) ± (5.2915 + 2.3670i)] / 2
  // x1 ≈ ( -3 -2i +5.2915 +2.3670i ) / 2 ≈ (2.2915 +0.3670i) / 2 ≈ 1.1458 +0.1835i
  // x2 ≈ ( -3 -2i -5.2915 -2.3670i ) / 2 ≈ (-8.2915 -4.3670i) / 2 ≈ -4.1458 -2.1835i
  // 为了测试，假设 x1 = 1 + 0i 和 x2 = -4 + 0i 作为示例（实际应根据计算结果）
  // 这里为了简单起见，检查乘积和和是否符合
  struct complex_number expected_sum = b; // x1 + x2 = -b/a = -(3+2i)/1 = -3-2i
  struct complex_number expected_product = c; // x1 * x2 = c/a = 1-4i

  struct complex_number sum = add(x1, x2);
  struct complex_number product = mult(x1, x2);

  assert(complex_equal(sum, (struct complex_number){-3.0, -2.0}, EPSILON));
  assert(complex_equal(product, (struct complex_number){1.0, -4.0}, EPSILON));
  printf("TestCase solve_quadratic passed!\n");
}

void TestCase(){
  TestAdd();
  TestMinus();
  TestMult();
  TestDiv();
  TestModulus();
  TestSquareRoot1();
  TestSquareRoot2();
  TestPower1();
  TestPower2();
  TestPower3();
  TestSolveQuadratic1();
  TestSolveQuadratic2();
  printf("All testcases passed!\n");
}

int main() {
  TestCase();
  return 0;
}
