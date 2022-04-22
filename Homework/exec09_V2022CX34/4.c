#include <stdio.h>

int a[13][13];

void generate(int);
void print(int);

int main(){
  int n;
  printf("Enter n:");
  scanf("%d", &n);
  generate(n);
  print(n);
}

void generate(int n){
  for (register int i = 0; i < n; i++)
    a[i][i + 1] = 1;
  for (register int i = 0; i < n; i++)
    for (register int j = 0; j < i; j++) 
      a[i][j + 1] = a[i - 1][j] + a[i - 1][j + 1];
}

void print(int n){
  for(register int i = 0; i < n; i++){
    for(register int j = 1; j < n - i; j++)
      printf("  ");
    for(register int j = 0; j <= i; j++)
      printf("%4d",a[i][j + 1]);
    printf("\n");
  }
}