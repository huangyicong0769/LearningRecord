#include <stdio.h>

int isWellNum(int);
void printWellNum(int);

int main(){
  int m, n;
  scanf("%d%d", &m, &n);
  int haveWellNum = 0;
  for (register int i = m; i <= n; i++)
    if (isWellNum(i) && (haveWellNum = 1))  printWellNum(i);
  if (haveWellNum == 0) printf("None\n"); 
}

int isWellNum(const int x){
  int sum = 0;
  for (register int i = 1; i < x; i++)
    if (x % i == 0) sum += i;
  return (sum == x);
}

void printWellNum(const int x){
  printf("%d = 1", x);
  for (register int i = 2; i < x; i++)
    if (x % i == 0) printf(" + %d", i);
  printf("\n");
}