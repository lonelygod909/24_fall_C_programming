#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
// Implement selection sort or bubble sort.
// Given an array of integers, sort them in
// the increasing order.
void bubblesort(int* list, int n) {
  for(int i = 0 ; i < n; i++){
    bool swapped = false;
		for (int j = 0 ; j < n - i - 1; j++){
			if(list[j] > list[j + 1]){
				 int temp = list[j];
				 list[j] = list[j + 1];
				 list[j + 1] = temp;
         swapped = true;
		  }
	  }
    if (!swapped) break;
  }
}
void sort(int* arr, int n) {
    // 初始增量设置为 n/2，每次减半
    for (int gap = n / 2; gap > 0; gap /= 2) {
        // 插入排序，gap 表示间隔
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j = i;
            
            // 将 arr[i] 插入到已经排好序的子序列中
            while (j >= gap && arr[j - gap] > temp) {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            
            arr[j] = temp;
        }
    }
}
//selection sort
void selectsort(int* list, int n) {
	for (int i = 0 ; i < n - 1; i++){
		for(int j = i + 1; j < n; j++){
			if (list[j] < list[i]){
				int temp = list[j];
				list[j] = list[i];
				list[i] = temp;
			}
		}
	}
}

void TestSort3() {
  int list[3] = {4, 1, 0};
  sort(list, 3);
  assert(list[0] == 0);
  assert(list[1] == 1);
  assert(list[2] == 4);
  printf("Passed Test Case 1\n"); 
}

int cmp(const void* first, const void* second) {
  int val_x = *(int*) first;
  int val_y = *(int*) second;
  if (val_x == val_y) {
    return 0;
  }
  return val_x < val_y ? -1 : 1;
}

// Generate n random integers as a test case.
void TestSortWithSize(int n, int test_case_number) {
  int list[n], list_cpy[n];
  int i;
  for (i = 0; i < n; i ++) {
    list[i] = rand(); 
    list_cpy[i] = list[i];
  }
  qsort(list_cpy, n, sizeof(int), cmp);
  sort(list, n);
  // Compare if two arrays are equal.
  for (i = 0; i < n; i ++) {
    assert(list[i] == list_cpy[i]);
  }
  printf("Passed Test Case %d\n", test_case_number); 
}

int main() {
  TestSort3();
  TestSortWithSize(10, 2);
  TestSortWithSize(100, 3);
  TestSortWithSize(1000, 4);
  TestSortWithSize(10000, 5);
  return 0;
}
