#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
#define reg register int
#define f(i, s, t) for (reg i = s; i <= t; i++)
#define il inline
#define ms(a, b) memset(a, b, sizeof(a))

const int N = 9, S1 = N * N * N * N * 4 + N, S2 = N * N * N + N,
          w[N * N + 1] = {0, 6, 6, 6, 6, 6, 6, 6,  6, 6, 6, 7, 7, 7, 7, 7, 7,
                          7, 6, 6, 7, 8, 8, 8, 8,  8, 7, 6, 6, 7, 8, 9, 9, 9,
                          8, 7, 6, 6, 7, 8, 9, 10, 9, 8, 7, 6, 6, 7, 8, 9, 9,
                          9, 8, 7, 6, 6, 7, 8, 8,  8, 8, 8, 7, 6, 6, 7, 7, 7,
                          7, 7, 7, 7, 6, 6, 6, 6,  6, 6, 6, 6, 6, 6};
int cnt, ans, r[S1], l[S1], u[S1], d[S1], row[S1], col[S1], ansk[S2], h[S2],
    s[S2];
bool v[N];

il void transform(int &r, int &c1, int &c2, int &c3, int &c4, int i, int j,
                  int k) {
  r = ((i - 1) * N + j - 1) * N + k;
  c1 = (i - 1) * N + j;
  c2 = N * N + (i - 1) * N + k;
  c3 = N * N * 2 + (j - 1) * N + k;
  c4 = N * N * 3 + (((i - 1) / 3) * 3 + (j - 1) / 3) * N + k;
}
il void init(int c) {
  f(i, 0, c) {
    r[i] = i + 1, l[i] = i - 1;
    u[i] = d[i] = i;
  }
  r[c] = 0, l[0] = c;
  ms(h, -1), ms(s, 0);
  cnt = c + 1;
}
il void link(int R, int C) {
  s[C]++;
  row[cnt] = R, col[cnt] = C;
  u[cnt] = C, d[cnt] = d[C];
  u[d[C]] = cnt, d[C] = cnt;
  if (h[R] == -1)
    h[R] = l[cnt] = r[cnt] = cnt;
  else {
    l[cnt] = l[h[R]], r[cnt] = h[R];
    r[l[h[R]]] = cnt, l[h[R]] = cnt;
  }
  cnt++;
}
il void remove(int C) {
  l[r[C]] = l[C], r[l[C]] = r[C];
  for (reg i = d[C]; i != C; i = d[i])
    for (reg j = r[i]; j != i; j = r[j])
      u[d[j]] = u[j], d[u[j]] = d[j], s[col[j]]--;
}
il void resume(int C) {
  for (reg i = u[C]; i != C; i = u[i])
    for (reg j = l[i]; j != i; j = l[j]) u[d[j]] = d[u[j]] = j, s[col[j]]++;
  l[r[C]] = r[l[C]] = C;
}
bool dance(int dep) {
  if (r[0] == 0) {
    reg tmp = 0;
    f(i, 0, dep - 1) tmp += w[ansk[i] / N + 1] * (ansk[i] % N + 1);
    ans = max(ans, tmp);
    return 1;
  }
  reg c = r[0];
  for (reg i = r[0]; i != 0; i = r[i])
    if (s[c] > s[i]) c = i;
  remove(c);
  for (reg i = d[c]; i != c; i = d[i]) {
    ansk[dep] = row[i] - 1;
    for (reg j = r[i]; j != i; j = r[j]) remove(col[j]);
    dance(dep + 1);
    for (reg j = l[i]; j != i; j = l[j]) resume(col[j]);
  }
  resume(c);
  return 0;
}

int main() {
  init(N * N * 4);
  f(i, 1, 9) f(j, 1, 9) {
    reg a;
    scanf("%d", &a);
    if (a) {
      reg r, c1, c2, c3, c4;
      transform(r, c1, c2, c3, c4, i, j, a);
      link(r, c1), link(r, c2), link(r, c3), link(r, c4);
      v[c1] = v[c2] = v[c3] = v[c4] = 1;
    }
  }
  f(i, 1, 9) f(j, 1, 9) f(k, 1, 9) {
    reg r, c1, c2, c3, c4;
    transform(r, c1, c2, c3, c4, i, j, k);
    if (v[c1] || v[c2] || v[c3] || v[c4]) continue;
    link(r, c1), link(r, c2), link(r, c3), link(r, c4);
  }
  dance(0);
  printf("%d\n", ans);
}