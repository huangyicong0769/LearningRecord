#include <cstdio>
#include <iostream>
#define SIZE 100006
#define reg register int
#define f(i, s, t) for (reg i = s; i != t + 1; i++)
using namespace std;

int N, s[SIZE], f[SIZE], d[SIZE], W[SIZE], q[SIZE];

int main() {
  scanf("%d", &N);
  for (reg i = N; i; i--) scanf("%d", &W[i]);
  f(i, 1, N) s[i] = s[i - 1] + W[i];
  reg l = 1, r = 0;
  f(i, 1, N) {
    while (l <= r && f[q[l]] <= s[i] - s[q[l]]) l++;
    f[i] = s[i] - s[q[l - 1]];
    d[i] = d[q[l - 1]] + 1;
    while (l <= r && f[i] + s[i] <= f[q[r]] + s[q[r]]) r--;
    q[++r] = i;
  }
  printf("%d\n", d[N]);
}