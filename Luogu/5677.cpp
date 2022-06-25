#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 300000;

ll a[MAXN + 5], c[MAXN + 5];
int n, m, b[MAXN + 5];

struct Query{
  int l, r, i;
  bool operator<(Query x){return this->r < x.r;}
}q[MAXN + 5];

inline int read(){
  register int x = 0;
  register char ch;
  for (ch = getchar(); ch < '0' || ch > '9'; ch = getchar());
  for (; ch >= '0' && ch <= '9'; ch = getchar())
    x = x*10 + ch - '0';
  return x;
}

bool camp1(int x, int y){return a[x] < a[y];}

int lowbit(int x){return x & (-x);}

void add(int x){
  if (x == 0) return;
  for (; x <= n; x += lowbit(x)) c[x] ++;
}

ll query(int x){
  if (x == 0) return 0;
  ll sum = 0;
  for (; x; x -= lowbit(x)) sum += c[x];
  return sum;
}

int main(){

  n = read(); m = read();
  for (register int i = 1; i <= n; i++){
    a[i] = read();
    b[i] = i;
  }
  for (register int i = 1; i <= m; i++){
    q[i].l = read();
    q[i].r = read();
    q[i].i = i;
  }

  sort(b + 1, b + n + 1, camp1);
  sort(q + 1, q + m + 1);
  
  vector<pair<int, int>> p;
  p.push_back(make_pair(max(b[1], b[2]), min(b[1], b[2])));
  p.push_back(make_pair(max(b[n], b[n - 1]), min(b[n], b[n - 1])));
  for (register int i = 2; i < n; i++){
    if (a[b[i]] - a[b[i - 1]] <= a[b[i + 1]] - a[b[i]])
      p.push_back(make_pair(max(b[i], b[i - 1]), min(b[i], b[i - 1])));
    if (a[b[i]] - a[b[i - 1]] >= a[b[i + 1]] - a[b[i]])
      p.push_back(make_pair(max(b[i], b[i + 1]), min(b[i], b[i + 1])));
  }

  sort(p.begin(), p.end());
  
  ll ans = 0;
  auto j = p.begin();
  for (register int i = 1; i <= m; i++){
    for (;j < p.end() && (*j).first <= q[i].r; j++) add((*j).second);
    ans += (query(q[i].r) - query(q[i].l - 1))*q[i].i;
  }

  printf("%lld\n", ans);
}