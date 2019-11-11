#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#define reg register int
#define f(i, s, t) for (reg i = s; i != t + 1; i++)
#define mc(a, b) memcpy(a, b, sizeof(a))
using namespace std;

const int INF = 0x3f3f3f3f, SIZE = 106;
int N, T, S, E, tot=100;
struct Matrix {
  int a[SIZE][SIZE];
  inline void pre() { f(i, 1, tot) f(j, 1, tot) a[i][j] = INF; }
} st, ed;
map<int, int> m;

Matrix mul(Matrix a, Matrix b) {
  Matrix c;
  c.pre();
  f(i, 1, tot) f(j, 1, tot) f(k, 1, tot) c.a[i][j] =
      min(c.a[i][j], a.a[i][k] + b.a[k][j]);
  return c;
}

int main() {
  freopen("input.txt", "r", stdin);
  scanf("%d%d%d%d", &N, &T, &S, &E);
  st.pre();
  tot = 0;
  f(i, 1, T) {
    reg a, b, c;
    scanf("%d%d%d", &c, &a, &b);
    a = m[a] ? m[a] : (m[a] = ++tot);
    b = m[b] ? m[b] : (m[b] = ++tot);
    st.a[a][b] = st.a[b][a] = c;
  }
  mc(ed.a, st.a);
  for (N--; N; N >>= 1, st = mul(st, st))
    if (N & 1) ed = mul(ed, st);
  printf("%d\n", ed.a[m[S]][m[E]]);
}