#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

const int FILE_NAME_MAX_LEN = 128;
const int STRING_MAX_LEN = 512;
const int MAX_LINE_LEN = 1024;

// Given the name of a text file and a target string, 
// searches for all occurrences of the target string
// in the file.
//
// For each match, it prints the line number and the
// entire line containing the target string.
int has_str(char* line, int linesize, char* target_str, int targetsize){
  int flag;
  int cnt = 0;
  for (int i = 0; i <= linesize - targetsize; i++){
    int flag = 1;
    for (int j = i; j <= i + targetsize - 1; j++){ 
      if (line[j] != target_str[j - i]){
        flag = 0;
        break;
      }
    }
    if (flag == 1){
      cnt += 1;
    }
  }
  return cnt;
}



int main(int argc , char** argv) {
  char file_name[FILE_NAME_MAX_LEN];
  char target_str[STRING_MAX_LEN];
  strcpy(file_name, argv[1]);
  strcpy(target_str, argv[2]);
  
  FILE* file_ptr;
  // Open the first file in reading mode
  file_ptr = fopen(file_name, "r");
  if (file_ptr == NULL) {
    printf("file %s can't be opened.\n", file_name);
    return EXIT_FAILURE;
  }

  // Read the file line by line.
  char line[MAX_LINE_LEN];
  int cnt = 1;
  while (fgets(line, MAX_LINE_LEN, file_ptr)) {
    int matchcount = has_str(line, strlen(line), target_str, strlen(target_str));
    if (matchcount > 0){
      printf("Found in number %d line:\n", cnt);
      printf("%s", line);
    }
    cnt++;
  }
  fclose(file_ptr);
  return 0;
}
