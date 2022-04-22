#include <stdio.h>

int a[10005];

void sort(int, int*);

int main(){
  int n;
  printf("Enter n:"); scanf("%d", &n);
  printf("Enter %d integer(s):", n);
  for (register int i = 0; i < n; i++) scanf("%d", a + i);
  sort(n, a);
  int ans = 0, num, cnt = 0;
  for (register int i = 0; i < n; i++) {
    if (i == 0 || a[i] != a[i - 1])
      cnt = 1;
    else cnt++;
    if (cnt > ans){
      ans = cnt;
      num = a[i];
    }
  }
  printf("Number %d repeats %d time(s) most\n", num, ans);
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