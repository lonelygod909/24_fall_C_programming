#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
/*
A rectangular chessboard consists of 'num_rows' rows and 'num_cols'
columns. Place 'num_queens' queens on the chessboard so that no
two queens share the same row, column, or diagonal. Return the
total number of different solutions.

We gurantee num_rows, num_cols, num_queens <= 10.
*/

void solve(int num_rows, int num_cols, int j, int num_queens, int* col_flag, int* row_flag, int* diag1, int* diag2, int* cnt ){
  if (num_queens == 0){
    (*cnt)++;
    return;
  }
  if (j == num_rows){
    return;
  }
  for (int i = 0; i < num_cols; i++){
    
    if (col_flag[i] == 1 || row_flag[j] == 1 || diag1[j - i + num_cols - 1] == 1 || diag2[i + j] == 1){
      continue;
    }

    col_flag[i] = 1;
    row_flag[j] = 1;
    diag1[j - i + num_cols - 1] = 1;
    diag2[i + j] = 1;
    
    solve(num_rows, num_cols ,  j + 1, num_queens - 1, col_flag, row_flag,diag1, diag2, cnt);
    
    col_flag[i] = 0;
    row_flag[j] = 0;
    diag1[j - i + num_cols - 1] = 0;
    diag2[i + j] = 0;

  }
  
  solve(num_rows, num_cols ,  j + 1, num_queens , col_flag, row_flag,diag1, diag2, cnt);
  
}

int place_queens(int num_rows, int num_cols, int num_queens) {
  int* col_flag = (int*) malloc(num_cols * sizeof(int));
  for (int i = 0; i < num_cols; i++){
    col_flag[i] = 0;
  }

  int* row_flag = (int*) malloc(num_rows * sizeof(int));
  for (int j = 0 ; j < num_rows; j++){
    row_flag[j] = 0;
  }

  int* diag1 = (int*) malloc((num_cols + num_rows - 1) * sizeof(int));
  for (int i = 0; i < (num_cols + num_rows - 1) ; i++){
    diag1[i] = 0;
  }

  int* diag2 = (int*) malloc((num_cols + num_rows - 1) * sizeof(int));
  for (int i = 0 ; i < (num_cols + num_rows - 1); i++) {
    diag2[i] = 0;
  }
  // init arrs

  int cnt = 0; 
  solve(num_rows, num_cols, 0, num_queens, col_flag, row_flag, diag1, diag2, &cnt);
  
  free(col_flag);
  free(row_flag);
  free(diag1);
  free(diag2);

  return cnt;// change 0 to your answer
}

void TestCase() {
  // Test Case : 1
  assert(place_queens(1,1,1) == 1);
  printf("Passed TestCase1\n");
  
  // Test Case : 2
  assert(place_queens(2,2,2) == 0);
  printf("Passed TestCase2\n");
  
  // Test Case : 3
  assert(place_queens(3,3,3) == 0);
  printf("Passed TestCase3\n");
  
  // Test Case : 4
  assert(place_queens(4,4,4) == 2);
  printf("Passed TestCase4\n");
  
  // Test Case : 5
  assert(place_queens(5,5,5) == 10);
  printf("Passed TestCase5\n");

  // Test Case : 6
  assert(place_queens(6,6,6) == 4);
  printf("Passed TestCase6\n");

  // Test Case : 7
  assert(place_queens(7,7,7) == 40);
  printf("Passed TestCase7\n");

  // Test Case : 8
  assert(place_queens(8,8,8) == 92);
  printf("Passed TestCase8\n");

  // Test Case : 9
  assert(place_queens(9,9,9) == 352);
  printf("Passed TestCase9\n");

  // Test Case : 10
  assert(place_queens(10,10,10) == 724);
  printf("Passed TestCase10\n");
  
  // Test Case : 11
  assert(place_queens(3,8,3) == 140);
  printf("Passed TestCase11\n");
  
  // Test Case : 12
  assert(place_queens(4,5,4) == 12);
  printf("Passed TestCase12\n");
  
  // Test Case : 13
  assert(place_queens(5,9,4) == 3942);
  printf("Passed TestCase13\n");

  // Test Case : 14
  assert(place_queens(5,10,5) == 3916);
  printf("Passed TestCase14\n");
  
  printf("All Test Cases Passed!\n");
}

int main() {
  TestCase();
  return 0;
}