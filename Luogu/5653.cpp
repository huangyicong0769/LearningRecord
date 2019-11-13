#include <iostream>
#include <cstdio>
using namespace std;
#define reg register int
#define f(i, s, t) for (reg i = s; i <= t; i++)
#define il inline

const int SN = 1e6 + 6;
int N, K, a[SN], w[SN];

il int read() {}

int main() {
  N = read(), K = read();
  f(i, 1, N) a[i] = read();
  f(i, 1, N) w[i] = read() + i * K;
}
