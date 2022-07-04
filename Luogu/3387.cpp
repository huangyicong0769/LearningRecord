#include <bits/stdc++.h>
using std::vector;
using std::min;
using std::max;

const int MAXN = 10000;

vector<int> edge[MAXN + 5];
vector<int> edgeSCC[MAXN + 5];

int n, m, num, cntSCC, dfn[MAXN + 5], low[MAXN + 5], c[MAXN + 5], a[MAXN + 5], b[MAXN + 5], f[MAXN + 5];
int stack[MAXN + 5], top;
bool inStack[MAXN + 5];

int read() {
  register int x = 0;
  register char ch = getchar();
  while (ch < '0' || ch > '9')
    ch = getchar();
  for (; ch >= '0' && ch <= '9'; ch = getchar())
    x = x*10 + ch - '0';
  return x;
}

void tarjan(int x){
  dfn[x] = low[x] = ++num;
  stack[++top] = x;
  inStack[x] = 1;
  for (auto y : edge[x])
    if (dfn[y] == 0){
      tarjan(y);
      low[x] = min(low[x], low[y]);
    }else if (inStack[y]) 
      low[x] = min(low[x], dfn[y]);
  if (dfn[x] == low[x]){
    cntSCC++;
    int y;
    do{
      y = stack[top--];
      inStack[y] = 0;
      b[cntSCC] += a[y];
      c[y] = cntSCC;
    }while(x != y);
  }
}

void dp(int x){
  for (auto y : edgeSCC[x]){
    if (f[y] == 0) dp(y);
    f[x] = max(f[x], f[y]);
  }
  f[x] += b[x];
}

int main(){
  scanf("%d%d", &n, &m);
  for (register int i = 1; i <= n; i++ ) scanf("%d", a + i);
  for (register int i = 0; i < m; i++)
    edge[read()].push_back(read());
  num = cntSCC = 0;
  for (register int x = 1; x <= n; x++) 
    if (dfn[x] == 0) 
      tarjan(x);
  for (register int x = 1; x <= n; x++)
    for (auto y : edge[x])
      if (c[x] != c[y])
        edgeSCC[c[x]].push_back(c[y]);
  int ans = 0;
  for (register int x = 1; x <= cntSCC; x++){
    if (f[x]) continue;
    dp(x);
    ans = max(ans, f[x]);
  }
  printf("%d\n", ans);
}