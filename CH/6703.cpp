#include <bits/stdc++.h>
#define il inline
#define reg register
#define f(i, s, t) for (reg int i = s; i != t + 1; i++)
#define ms(a, b) memset(a, b, sizeof(a))
#define mc(a, b) memcpy(a, b, sizeof(a))
using namespace std;

typedef long long ll;
const ll P = 1e9 + 7, SN = 100007, SM = 200007, INF = 0x7fffffff;
ll TT, N, M, S, Q, T, totf, totb, fs[SN], ft[SN], Hf[SN], Hb[SN], Nf[SM],
    Nb[SM], Vf[SM], Vb[SM], Bf[SN], Bb[SN], Lf[SM], Lb[SM], inDe[SN], outDe[SN],
    d[SN], pre[SN], ds[SN], sum[SN], dt[SN], Laf[SN], path[SN], tDe[SN];

il void addForward(const ll &x, const ll &y, const ll &z) {
  Vf[++totf] = y, Laf[totf] = x, Lf[totf] = z, Nf[totf] = Hf[x], Hf[x] = totf,
  inDe[y]++;
}

il void addBackward(const ll &x, const ll &y, const ll &z) {
  Vb[++totb] = y, Lb[totb] = z, Nb[totb] = Hb[x], Hb[x] = totb, outDe[y]++;
}

il void topsortForward() {
  mc(tDe, inDe);
  fs[S] = 1;
  queue<int> q;
  f(i, 1, N) if (tDe[i] == 0) q.push(i);
  for (; q.size(); q.pop()) {
    const reg int x = q.front();
    for (reg int i = Hf[x]; i; i = Nf[i]) {
      const reg ll &y = Vf[i];
      (fs[y] += fs[x]) %= P;
      if (--tDe[y] == 0) q.push(y);
    }
  }
}

il void topsortBackward() {
  mc(tDe, outDe);
  ft[T] = 1;
  queue<int> q;
  f(i, 1, N) if (tDe[i] == 0) q.push(i);
  for (; q.size(); q.pop()) {
    const reg int x = q.front();
    for (reg int i = Hb[x]; i; i = Nb[i]) {
      const reg ll &y = Vb[i];
      (ft[y] += ft[x]) %= P;
      if (--tDe[y] == 0) q.push(y);
    }
  }
}

il void topsortSP() {
  mc(tDe, inDe);
  d[S] = 0;
  queue<int> q;
  f(i, 1, N) if (tDe[i] == 0) q.push(i);
  for (; q.size(); q.pop()) {
    const reg int x = q.front();
    for (reg int i = Hf[x]; i; i = Nf[i]) {
      const reg ll &y = Vf[i], &z = Lf[i];
      if (d[y] > d[x] + z) d[y] = d[x] + z, pre[y] = x;
      if (--tDe[y] == 0) q.push(y);
    }
  }
}

il void dpForward(const ll &cnt) {
  reg int cur = 1;
  f(i, 1, cnt) {
    while (d[path[i]] - d[path[cur]] > Q) cur++;
    ds[i] = ds[i - 1];
    reg ll tmp = sum[path[i]] - sum[path[cur]];
    if (Bf[path[cur]]) tmp += Q - (d[path[i]] - d[path[cur]]);
    ds[i] = max(ds[i], tmp);
  }
}

il void dpBackward(const ll &cnt) {
  for (reg int i = cnt, cur = cnt; i; i--) {
    while (d[path[cur]] - d[path[i]] > Q) cur--;
    dt[i] = dt[i + 1];
    reg ll tmp = sum[path[cur]] - sum[path[i]];
    if (Bb[path[cur]]) tmp += Q - (d[path[cur]] - d[path[i]]);
    dt[i] = max(dt[i], tmp);
  }
}

int main() {
  for (scanf("%lld", &TT); TT; TT--) {
    scanf("%lld%lld%lld%lld%lld", &N, &M, &S, &T, &Q);
    ms(Hf, 0), ms(Hb, 0), ms(sum, 0), ms(fs, 0), ms(ft, 0), ms(Bf, 0),
        ms(Bb, 0), ms(ds, 0), ms(dt, 0), ms(inDe, 0), ms(outDe, 0);
    totf = totb = 0;
    f(i, 1, N) d[i] = INF;
    S++, T++;
    totf = totb = 0;
    f(i, 1, M) {
      reg ll a, b, c;
      scanf("%lld%lld%lld", &a, &b, &c);
      a++, b++;
      addForward(a, b, c);
      addBackward(b, a, c);
    }
    topsortForward();
    topsortBackward();
    topsortSP();
    f(i, 0, totf) {
      const ll &x = Laf[i], y = Vf[i];
      if (fs[x] * ft[y] % P == fs[T]) {
        Bf[y] = Bb[x] = 1;
        sum[y] = Lf[i];
      }
    }
    if (d[T] == INF) {
      puts("-1");
      continue;
    }
    ll cnt = 0, p = T;
    do {
      path[++cnt] = p, p = pre[p];
    } while (p != S);
    path[++cnt] = S;
    reverse(path + 1, path + 1 + cnt);
    f(i, 1, cnt) sum[path[i]] += sum[path[i - 1]];
    dpForward(cnt);
    dpBackward(cnt);
    ll ans = INF;
    f(i, 1, cnt) ans = min(ans, sum[path[cnt]] - (ds[i] + dt[i]));
    printf("%lld\n", ans);
  }
}