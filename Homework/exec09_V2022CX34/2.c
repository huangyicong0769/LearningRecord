#include <stdio.h>

int a[10005];

void sort(int, int*);

int main(){
  // while (scanf("%d", &a[++a[0]]) != EOF);
  while (1){
    scanf("%d", &a[++a[0]]);
    if (getchar() == '\n') break;
  }
  sort(a[0], a+1);
  int k = 1;
  while (a[k] == 0) k++;
  int t = a[1];
  a[1] = a[k];
  a[k] = t;
  for (register int i = 1; i <= a[0]; i++) printf("%d", a[i]);
  printf("\n");
  return 0;
}

void sort(int n, int* a){
  for (register int i = 0; i < n; i++)
    for (register int j = i; j < n; j ++)
      if (a[i] > a[j]){
        int t = a[i];
        a[i] = a[j];
        a[j] = t;
      }
}