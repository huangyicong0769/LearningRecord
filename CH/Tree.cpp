// ykhoj 3355
// POJ 1741
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#define reg register
#define il inline
#define SIZE 40006
#define f(a, b, c) for (reg int a = b; a <= c; a++)
using namespace std;

int N, K, p, ans, tot, Ans, a[SIZE], b[SIZE], d[SIZE], cnt[SIZE], si[SIZE];
bool been[SIZE], del[SIZE];
vector<int> v1[SIZE], v2[SIZE];

bool comp(const int &x, const int &y) { return d[x] < d[y]; }

void dfs(const int &N, int x) {
  si[x] = 1;
  been[x] = 1;
  int max_part = 0;
  f(i, 0, v1[x].size() - 1) {
    const int &j = v1[x][i];
    if (been[j] || del[j]) continue;
    dfs(N, j);
    si[x] += si[j];
    max_part = max(max_part, si[j]);
  }
  max_part = max(max_part, N - si[x]);
  if (max_part < ans) {
    ans = max_part;
    p = x;
  }
}

void init(int x) {
  been[x] = 1;
  f(i, 0, v1[x].size() - 1) {
    const int &j = v1[x][i];
    if (been[j] || del[j]) continue;
    ++cnt[b[a[++tot] = j] = b[x]];
    d[j] = d[x] + v2[x][i];
    init(j);
  }
}

il void work(int n, int s) {
  // printf("========%d %d\n", n, s);
  // memset(a, 0, sizeof(a));
  // memset(b, 0, sizeof(b));
  memset(d, 0, sizeof(d));
  // memset(si, 0, sizeof(si));
  memset(cnt, 0, sizeof(cnt));
  memset(been, 0, sizeof(been));
  ans = n;
  dfs(n, s);
  del[a[tot = 1] = b[p] = p] = 1;
  ++cnt[p];
  memset(been, 0, sizeof(been));
  f(i, 0, v1[p].size() - 1) {
    const int &j = v1[p][i];
    if (been[j] || del[j]) continue;
    ++cnt[a[++tot] = b[j] = j];
    d[j] = v2[p][i];
    init(j);
  }
  sort(a + 1, a + 1 + tot, comp);
  reg int l = 1, r = tot;
  --cnt[b[a[1]]];
  // f (i, 1, tot) printf("%d ", a[i]); printf("\n");
  // f (i, 1, N) printf("%d ", b[i]); printf("\n");
  // f (i, 1, N) printf("%d ", d[i]); printf("\n");
  // f (i, 1, N) printf("%d ", si[i]); printf("\n");
  // f (i, 1, N) printf("%d ", cnt[i]); printf("\n");
  // f (i, 1, N) printf("%d ", been[i]); printf("\n");
  // f (i, 1, N) printf("%d ", del[i]); printf("\n");
  for (; l < r; l++) {
    for (; d[a[l]] + d[a[r]] > K; r--) --cnt[b[a[r]]];
    Ans += r - l - cnt[b[a[l]]];
    --cnt[b[a[l + 1]]];
  }
  reg int now = p;
  f(i, 0, v1[now].size() - 1) {
    const int &j = v1[now][i];
    if (del[j]) continue;
    work(si[j], j);
  }
}

int main() {
  scanf("%d", &N);
  f(i, 1, N - 1) {
    reg int u, v, l;
    scanf("%d%d%d", &u, &v, &l);
    v1[u].push_back(v);
    v2[u].push_back(l);
    v1[v].push_back(u);
    v2[v].push_back(l);
  }
  scanf("%d", &K);
  Ans = 0;
  memset(del, 0, sizeof(del));
  work(N, 1);
  printf("%d\n", Ans);
  f(i, 1, N) v1[i].clear(), v2[i].clear();
}