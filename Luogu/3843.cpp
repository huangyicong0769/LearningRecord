#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;
#define reg register int
#define f(i, s, t) for (reg i = s; i < t; i++)
#define il inline

const int SN = 106;
int c[2], s[2], p[2][2], e[2][SN], f[2][SN][2];

int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }

int lcm(int a, int b) { return a * b / gcd(a, b); }

double dis(int ax, int ay, int bx, int by) {
  return sqrt((ax - bx) * (ax - bx) + (ay - by) * (ay - by));
}

int main() {
  f(k, 0, 2) {
    scanf("%d%d%d", &p[k][0], &p[k][1], &c[k]);
    f(i, 0, c[k]) {
      reg len; char dir[2];
      scanf("%d%s", &len, dir);
      f[k][i][dir[0] == 'Y'] = len / abs(len);
      e[k][i] = abs(len);
      s[k] += abs(len);
    }
  }
  reg i[2] = {0}, j[2] = {0};
  double ans = 1e20 + 6;
  f(t, 0, lcm(s[0], s[1])) {
    ans = min(ans, dis(p[0][0], p[0][1], p[1][0], p[1][1]));
    f(k, 0, 2) f(d, 0, 2) p[k][d] += f[k][i[k]][d];
    f(k, 0, 2) if (++j[k] == e[k][i[k]]) (++i[k]) %= c[k], j[k] = 0;
  }
  printf("%.2lf\n", ans);
}