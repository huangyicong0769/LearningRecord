#include <stdio.h>

int main() {
  int l = 0, b = 0, d = 0, o = 0;
  char ch;
  while (scanf("%c", &ch) != EOF) {
    if (ch >= 'A' && ch <= 'Z' || ch >= 'a' && ch <= 'z') l++;
    else if (ch >= '0' && ch <= '9') d++;
    else if (ch == ' ' || ch == '\n') b++;
    else o++; 
  }
  printf("letter = %d, blank = %d, digit = %d, other = %d\n", l, b - 1, d, o);
  return 0;
}