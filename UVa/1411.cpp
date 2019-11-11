#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <cmath>
using namespace std;
#define reg register int
#define f(i, s, t) for (reg i = s; i != t + 1; i++)
#define il inline
#define ms(a, b) memset(a, b, sizeof(a))

const int SN = 206, SM = SN * SN, inf = 0x3f3f3f3f;
const double Exp = 1e-5;
int N, S, T, tot, ans, Head[SN], Next[SM], Ver[SM], Cap[SM], incf[SN], pre[SN];
double Wei[SM], d[SN];
bool v[SN];
struct Point {
  int x, y;
} a[SN], b[SN];

il void add(int x, int y, double w) {
  Ver[++tot] = y, Wei[tot] = w, Cap[tot] = 1, Next[tot] = Head[x],
  Head[x] = tot;
  Ver[++tot] = x, Wei[tot] = -w, Cap[tot] = 0, Next[tot] = Head[y],
  Head[y] = tot;
}

il double di(Point a, Point b) {
  return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

il bool spfa() {
  ms(v, 0), ms(incf, 0);
  f(i, S, T) d[i]=inf;
  queue<int> q;
  q.push(S);
  d[S] = 0, incf[S] = inf, v[S] = 1;
  while (q.size()) {
    reg x = q.front();
    q.pop(), v[x] = 0;
    for (reg i = Head[x]; i; i = Next[i]) {
      if (!Cap[i]) continue;
      reg y = Ver[i];
      if (d[y] > d[x] + Wei[i]) {
        d[y] = d[x] + Wei[i];
        pre[y] = i;
        incf[y] = min(incf[x], Cap[i]);
        if (!v[y]) q.push(y), v[y] = 1;
      }
    }
  }
  return d[T] < inf - Exp;
}

il void update() {
  for (reg x = T, i = pre[x]; x != S; x = Ver[i ^ 1], i = pre[x])
    Cap[i] -= incf[T], Cap[i ^ 1] += incf[T];
}

int main() {
  while (cin >> N) {
    ms(Head, 0);
    tot = 1, S = 0, T = 2 * N + 1;
    f(i, 1, N) scanf("%d%d", &a[i].x, &a[i].y);
    f(i, 1, N) scanf("%d%d", &b[i].x, &b[i].y);
    f(i, 1, N) add(S, i, 0);
    f(i, 1, N) add(i + N, T, 0);
    f(i, 1, N) f(j, 1, N) add(i, j + N, di(a[i], b[j]));
    // printf("%d %d %d\n", i, j, di(a[i], b[j]));
    while (spfa()) update();
    f(i, 1, N) {
      for (reg j = Head[i]; j; j = Next[j]) {
        if (Cap[j]) continue;
        printf("%d\n", Ver[j] - N);
        break;
      }
    }
    // puts("");
  }
}