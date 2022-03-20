#include <stdio.h>

int main() {
  int year;
  scanf("%d", &year);
  if (year <= 2000 || year > 2100) {
    printf("Invalid year!\n");
    return 0;
  }
  int isGapYear = 1;
  for (register int i = 2001; i <= year; i++) 
    if (i % 4 == 0 && i%100 || i%400 == 0) isGapYear = 0, printf("%d\n", i);
  if (isGapYear) printf("None\n");
  return 0;
}