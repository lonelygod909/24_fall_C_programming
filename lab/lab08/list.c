#include <stdio.h>
#include <assert.h>
// Add a new element 'new_number' to a sorted list.
// And update the length of the list.
void insert(int* list, int* len, int new_number) {
  (*len)++;
  if (new_number >= list[*len - 2]){
    list[*len - 1] = new_number;
    return;
  }
  if (new_number <= list[0]){
    list[0] = new_number;
    return;
  }
  for (int i = 0; i < *len - 1; i++){
    if (new_number >= list[i] && new_number <= list[i + 1]){
      
      for (int j = i + 1; j < *len - 1 ; j++){
        list[j + 1] = list[j];
      }
      list[i + 1] = new_number;

    }
  }
}

// Look for an element 'target' in the sorted list.
// If found, return its index; otherwise, return -1.
int search(int* list, int len, int target) {
  int end = len - 1;
  int begin = 0;
  int mid = (end + begin) / 2;
  while (begin <= end) {
    if (list[mid] == target){
      return mid;
    }
    else if (list[mid] < target){
      begin = mid + 1;
    }
    else{
      end = mid - 1;
    }
    mid = (begin + end) / 2;
  }
  return -1;
}

// Remove an element 'target' from the sorted list.
// If the target is found, update the length and
// return 1; otherwise, return 0.
int delete(int* list, int* len, int target) {
  int index = search(list, *len, target);
  if (index == -1){
    return 0;
  }
  for (int i = index ; i < *len - 1 ; i++){
    list[i] = list[i + 1];
  }
  
  list[*len - 1] = 0;
  (*len)--;

  return 1;
}

void InsertTestCase() {
  // Insert test case : 
  int list[100] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
  int len = 10;
  insert(list, &len, 30);
  assert(len == 11 && list[10] == 30);
  printf("Passed InsertCase1");
  insert(list, &len, 15);
  assert(len == 12 && list[6] == 15);
  printf("Passed InsertCase2");
  insert(list, &len, 1);
  assert(len == 13 && list[0] == 1);
  printf("Passed InsertCase3");
  printf("Passed All InsertTestCase1\n");
}

void SearchTestCase() {
  // Search test case : 
  int list[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
  int len = 10;
  
  assert(search(list,len,2) == 0);
  printf("Passed SearchCase1");
  assert(search(list,len,15) == -1);
  printf("Passed SearchCase2");
  assert(search(list,len,29) == 9);
  printf("Passed SearchCase3");
  
  printf("Passed All SearchTestCase1\n");
}

void DeleteTestCase() {
  // Dlete test case : 
  int list[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
  int len = 10;
  assert(delete(list, &len, 15) == 0 && len == 10);
  printf("Passed DeleteCase1");
  assert(delete(list, &len, 2) == 1 && len == 9 && list[0] == 3 && list[8] == 29 );
  printf("Passed DeleteCase2");
  assert(delete(list, &len, 17) == 1 && len == 8 && list[5] == 19 && list[7] == 29);
  printf("Passed DeleteCase3");
  printf("Passed All DeleteTestCase\n");
}

int main() {
  InsertTestCase();
  SearchTestCase();
  DeleteTestCase();
  return 0;
}