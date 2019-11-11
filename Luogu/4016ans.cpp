#include <bits/stdc++.h>
using namespace std;
const int Mmax = 1910;
const int Nmax = 210;
const int inf = 20010509;
int n, m, s, t, p1, p2, p3, to[Mmax << 1], net[Mmax << 1], mf[Mmax << 1],
    mo[Mmax << 1], tails = 1, fr[Nmax];
void add(int froms, int tos, int mfs, int money) {
  to[++tails] = tos;
  net[tails] = fr[froms];
  mf[tails] = mfs;
  mo[tails] = money;
  fr[froms] = tails;
}
void auto_add(int st, int en, int mft, int mo) {
  add(st, en, mft, mo), add(en, st, 0, -mo);
}
int lastp[Nmax], useds[Nmax], flown[Nmax], dis[Nmax], ndo, p4;
bool inqu[Nmax];
queue<int> ready;
bool SPFA() {
  memset(inqu, 0, sizeof(inqu));
  memset(dis, 20010509, sizeof(dis));
  memset(flown, 20010509, sizeof(flown));
  while (!ready.empty()) ready.pop();
  ready.push(s);
  dis[s] = 0;
  inqu[s] = 1;
  // flown[s] = 20010509;
  lastp[t] = 0;
  while (!ready.empty()) {
    ndo = ready.front();
    ready.pop();
    inqu[ndo] = 0;
    for (int i = fr[ndo]; i; i = net[i]) {
      if (dis[to[i]] <= dis[ndo] + mo[i] || mf[i] == 0) continue;
      dis[to[i]] = dis[ndo] + mo[i];
      flown[to[i]] = min(mf[i], flown[ndo]);
      useds[to[i]] = i;
      lastp[to[i]] = ndo;
      if (!inqu[to[i]]) {
        inqu[to[i]] = 1;
        ready.push(to[i]);
      }
    }
  }
  return lastp[t] != 0;
}
int maxflow = 0, mincost = 0, ppo;
void Dinic() {
  while (SPFA()) {
    maxflow += flown[t];
    ppo = t;
    mincost += flown[t] * dis[t];
    while (ppo != s) {
      mf[useds[ppo]] -= flown[t];
      mf[useds[ppo] ^ 1] += flown[t];
      ppo = lastp[ppo];
    }
  }
}
int x[Nmax], sum;
int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &x[i]);
    sum += x[i];
  }
  sum /= n;
  s = 208;
  t = 209;
  for (int i = 1; i <= n; ++i) x[i] -= sum;
  for (int i = 1; i <= n; ++i) {
    if (x[i] > 0)
      auto_add(s, i, x[i], 0);
    else if (x[i] < 0)
      auto_add(i, t, -x[i], 0);
  }
  for (int i = 1; i <= n; ++i) {
    if (i != 1) auto_add(i, (i - 1), inf, 1);
    if (i != n) auto_add(i, (i + 1), inf, 1);
  }
  auto_add(1, n, inf, 1);
  auto_add(n, 1, inf, 1);
  Dinic();
  printf("%d", mincost);
  return 0;
}