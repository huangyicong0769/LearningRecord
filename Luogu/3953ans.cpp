#include <cstdio>
#include <cstring>
#define re register int
#define fp(i, a, b) for (re i = a, I = b; i <= I; ++i)
#define file(s) freopen(s ".in", "r", stdin), freopen(s ".out", "w", stdout)
char ss[1 << 17], *A = ss, *B = ss;
inline char gc() {
  return A == B && (B = (A = ss) + fread(ss, 1, 1 << 17, stdin), A == B) ? -1
                                                                         : *A++;
}
template <class T>
inline void sdf(T& x) {
  char c;
  T y = 1;
  while (c = gc(), (c < 48 || 57 < c) && c != -1)
    if (c == '-') y = -1;
  x = c ^ 48;
  while (c = gc(), 47 < c && c < 58) x = (x << 1) + (x << 3) + (c ^ 48);
  x *= y;
}
const int N = 1e5 + 5, M = 2e5 + 5;
typedef int arr[N];
struct eg {
  int nx, to, w;
} e[M << 1];
int T, n, m, K, P, ce, f[N][51];
arr dis, f1, fn;
bool in[N][51];
namespace seg {
int tr[N << 2], sgt;
inline void Set(re n) {
  sgt = 1;
  while (sgt <= n) sgt <<= 1;
  --sgt;
  tr[0] = N - 1;
}
inline void clr() { fp(i, 1, (sgt << 1) + 1) tr[i] = 0; }
inline int cmp(const re& a, const re& b) { return dis[a] < dis[b] ? a : b; }
inline void mdy(re x, re w) {
  for (re i = x + sgt; dis[tr[i]] > w; i >>= 1) tr[i] = x;
  dis[x] = w;
}
inline void del(re x) {
  tr[x += sgt] = 0;
  x >>= 1;
  while (x) tr[x] = cmp(tr[x << 1], tr[x << 1 | 1]), x >>= 1;
}
}  // namespace seg
using namespace seg;
void dij() {
  memset(dis, 9, 4 * (n + 1));
  clr();
  mdy(n, 0);
  fp(T, 1, n) {
    re u = tr[1];
    del(u);
    for (re i = fn[u], v; i; i = e[i].nx)
      if (dis[v = e[i].to] > dis[u] + e[i].w) mdy(v, dis[u] + e[i].w);
  }
}
inline void add(re u, re v, re w, re* fi) {
  e[++ce] = (eg){fi[u], v, w};
  fi[u] = ce;
}
inline void mod(re& a) { a >= P ? a -= P : 0; }
int dfs(re u, re k) {
  if (in[u][k]) return -1;
  if (f[u][k]) return f[u][k];
  in[u][k] = 1;
  u == n ? f[u][k] = 1 : 0;
  for (re i = f1[u], v, w, tp; i; i = e[i].nx)
    if ((tp = dis[v = e[i].to] - dis[u] + e[i].w) <= k) {
      if ((w = dfs(v, k - tp)) == -1) return f[u][k] = -1;
      mod(f[u][k] += w);
    }
  return in[u][k] = 0, f[u][k];
}
int main() {
  // #ifndef ONLINE_JUDGE
  //     file("park");
  // #endif
  sdf(T);
  while (T--) {
    memset(f, 0, sizeof f);
    memset(in, 0, sizeof in);
    sdf(n);
    sdf(m);
    sdf(K);
    sdf(P);
    Set(n);
    re u, v, w;
    memset(f1, ce = 0, 4 * (n + 1));
    memset(fn, 0, 4 * (n + 1));
    while (m--) sdf(u), sdf(v), sdf(w), add(u, v, w, f1), add(v, u, w, fn);
    dij();
    printf("%d\n", dfs(1, K));
  }
  return 0;
}