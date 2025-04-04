#include <stdio.h>
#include <assert.h>
#include <stdlib.h>


int fib_period(int p) {
    int* a = (int*) malloc(p * p * sizeof(int));  
    a[1] = 1;
    for (int i = 2; i < p * p; i++) {
        a[i] = (a[i - 1] + a[i - 2]) % p;
        if (a[i] == 0 && a[i - 1] == 1) {
            free(a);
            return i;  
        }
    }

    free(a);
    return 0;  
}

int helper(long long n, int p, int* memo) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    if (memo[n] != -1) return memo[n];  
    memo[n] = (helper(n - 1, p, memo) + helper(n - 2, p, memo)) % p;
    return memo[n];
}

int fib(long long n, int p) {
    int per = fib_period(p);  
    int* memo = (int*) malloc((per + 1) * sizeof(int));  
    for (int i = 0; i <= per; i++) memo[i] = -1;  
    int result = helper(n % per, p, memo);  // Get Fibonacci number mod p
    free(memo);
    return result;
}

// Test case 1: n:1234567 p= 17 result=16
void TestCase1() {
    int res;
    res = fib(1234567, 17);
    assert(res == 16);
    printf("Passed TestCase1\n");
}

// Test case 2: n=10000000000 p=1235 result=55
void TestCase2() {
    int res;
    res = fib(10000000000, 1235);
    assert(res == 55);
    printf("Passed TestCase2\n");
}

// Test case 3: n=100000000000 result=439
void TestCase3() {
    int res;
    res = fib(100000000000, 790);
    assert(res == 635);
    printf("Passed TestCase3\n");
}

int main() {
    TestCase1();
    TestCase2();
    TestCase3();
    return 0;
}
