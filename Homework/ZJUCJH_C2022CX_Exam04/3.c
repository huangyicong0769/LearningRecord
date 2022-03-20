#include <stdio.h>

int main() {
  int a, b;
  char ch;
  scanf("%d %c %d", &a, &ch, &b);
  printf("%d %c %d", a, ch, b);
  switch (ch) {
  case '+':
    printf("%d\n", a + b);
    break;

  case '-':
    printf("%d\n", a - b);
    break;

  case '*':
    printf("%d\n", a * b);
    break;

  case '/':
    printf("%d\n", a / b);
    break;

  case '%':
    printf("%d\n", a % b);
    break;

  default:
    printf("ERROR\n");
    break;
  }
  return 0;
}