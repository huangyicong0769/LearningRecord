#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;
#define reg register ll
#define f(i, s, t) for (reg i = s; i <= t; i++)
typedef long long ll;

const int P = 9901;

inline ll fp(ll a, int n) {
  reg ans = 1;
  for (; n; n >>= 1) {
    if (n & 1) ans = ans * a % P;
    a = a * a % P;
  }
  return ans;
}

int main(int argc, const char** argv) {
  reg A, B, ans = 1;
  scanf("%lld%lld", &A, &B);
  f(i, 2, sqrt(A)) {
    if (A % i) continue;
    reg c = 0;
    while (A % i == 0) A /= i, c++;
    c *= B;
    if ((i - 1) % P)
      ans = ans * (fp(i, c + 1) - 1) % P * fp(i - 1, P - 2) % P;
    else
      ans = ans * (c + 1) % P;
  }
  // printf("%lld\n", (A - 1) % P);
  if (A != 1) {
    reg c = B;
    // printf("%lld\n", ans);
    if ((A - 1) % P)
      ans = ans * (fp(A, c + 1) - 1) % P * fp(A - 1, P - 2) % P;
    else
      ans = ans * (c + 1) % P;
  }
  printf("%lld\n", ans);
  return 0;
}