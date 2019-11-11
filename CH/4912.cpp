#pragma GCC optimize(3,"Ofast","inline")
#include <cstdio>
#include <iostream>
#include <vector>
#define reg register
#define il inline
#define SIZE 300006
#define ll long long
#define f(i, s, t) for (reg int i = s; i <= t; i++)
using namespace std;

struct Event {
  int l, r;
  ll val;
} at[SIZE];

int N, M, K, q[SIZE], rq[SIZE], lq[SIZE];
ll ans[SIZE], c[SIZE], hope[SIZE];
vector<int> st[SIZE];

il void add(int x, ll y) {
  for (; x <= M; x += x & -x) c[x] += y;
}

il ll ask(int x) {
  ll ans = 0;
  for (; x; x -= x & -x) ans += c[x];
  return ans;
}

il void get(int i, int w) {
  reg ll num = w * at[i].val;
  if (at[i].l > at[i].r) add(1, num);
  add(at[i].l, num);
  add(at[i].r + 1, -num);
}

void solve(int l, int r, int x, int y) {
  if (x > y) return;
  if (l == r) {
    f(i, x, y) ans[q[i]] = l;
    return;
  }
  int mid = (l + r) >> 1, lc = 0, rc = 0;
  f(i, l, mid) get(i, 1);
  f(i, x, y) {
    ll cnt = 0;
    f(j, 0, (int)st[q[i]].size() - 1) {
      cnt += ask(st[q[i]][j]);
      if (cnt > hope[q[i]]) break;
    }
    if (cnt >= hope[q[i]])
      lq[++lc] = q[i], ans[q[i]] = l;
    else
      rq[++rc] = q[i], hope[q[i]] -= cnt;
  }
  f(i, l, mid) get(i, -1);
  f(j, 1, lc) q[x + j - 1] = lq[j];
  f(j, 1, rc) q[x + lc + j - 1] = rq[j];
  solve(l, mid, x, x + lc - 1);
  solve(mid + 1, r, x + lc, y);
}

il ll read(){
  reg ll x=0; reg char ch=getchar();
  for(; ch<'0' || ch>'9'; ch=getchar());
  for(; ch>='0' && ch<='9'; ch=getchar()) x=x*10+ch-'0';
  return x;
}

int main() {
  N=read(), M=read();
  f(i, 1, M) st[read()].push_back(i);
  f(i, 1, N) hope[i]=read();
  K=read();
  f(i, 1, K) at[i].l=read(), at[i].r=read(), at[i].val=read();
  f(i, 1, N) q[i] = i;
  ++K;
  at[K].l = 1, at[K].r = M, at[K].val = 0x3f3f3f3f;
  solve(1, K, 1, N);
  f(i, 1, N) ans[i] != K ? printf("%lld\n", ans[i]) : puts("NIE");
}