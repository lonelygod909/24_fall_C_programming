#include <stdio.h>
#include <assert.h>

// Given a specific date (year, month, day), this function
// and returns the total number of days that have passed
// since January 1st, Year 1.
// if date is illegal,return -1. 
struct date
{
  int year;
  int month;
  int day;
};

int is_leap_year(int year) {
  if (year % 400 == 0 || year % 4 == 0 && year % 100 != 0)
  return 1;
  return 0;
}

int count_leap_years_til_today(int year, int month) {
  int cnt = 0;
  for (int i = 1; i <= year - 1; i++){
    if (is_leap_year(i)){
      cnt++;
    }
  }
  return cnt;
}

int calculate_days(int month, int day) {
    int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int total_days = 0;
    for (int i = 0; i < month - 1; i++) {
        total_days += days_in_month[i];
    }
    total_days += day;
    return total_days;
}

int date_to_days(struct date date) {
  int year = date.year;
  int month = date.month;
  int day = date.day;
  if (!is_leap_year(year) && month == 2 && day == 29)
  return -1;
  int a = (year - 1) * 365 + count_leap_years_til_today(year , month) + calculate_days(month, day);
  if (is_leap_year(year) && month > 2){
    a++;
  }
  return a - 1;
}



void TestCase1() {
  // Test Case 1: 2016.2.29
  struct date date = {2016, 2, 29};
  int days;
  days=date_to_days(date);
  assert(days==736022);
  printf("Passed TestCase1\n");
}

void TestCase2() {
  // Test Case 1: 2017.2.29
  struct date date = {2017, 2, 29};
  int days;
  days=date_to_days(date);
  assert(days==-1);
  printf("Passed TestCase2\n");
}

void TestCase3() {
  // Test Case 3: 2024.10.12
  struct date date ={2024, 10, 12};
  int days;
  days=date_to_days(date);
  assert(days==739170);
  printf("Passed TestCase3\n");
}




int main() {
  TestCase1();
  TestCase2();
  TestCase3();
  return 0;
}
