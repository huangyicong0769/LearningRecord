#include <stdio.h>

int a[23][23];

int main(){
  int m, n;
  printf("Enter m, n:");
  scanf("%d%d", &m, &n);
  printf("Enter an array:\n");
  for (register int i = 0; i < m; i++)
    for (register int j = 0; j < n; j++)
      scanf("%d", &a[i][j]);
  for (register int i = 1; i < m - 1; i++)
    for (register int j = 1; j < n - 1; j++)
      if (a[i][j] > a[i - 1][j] && a[i][j] > a[i][j - 1] &&
          a[i][j] > a[i + 1][j] && a[i][j] > a[i][j + 1])
        printf("%d %d %d\n", a[i][j], i + 1, j + 1);
}