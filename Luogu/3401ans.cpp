#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>
#define inf 2147483647
#define ri register int
#define ll long long
#define mid (l + r >> 1)
#define lson (o << 1)
#define rson ((o << 1) + 1)
using namespace std;
inline void read(int &x) {
  x = 0;
  char t = getchar();
  bool f = 0;
  while (t < '0' || t > '9') {
    if (t == '-') f = 1;
    t = getchar();
  }
  while (t >= '0' && t <= '9') {
    x = (x << 3) + (x << 1) + t - '0';
    t = getchar();
  }
  if (f) x = -x;
}
inline void addedge(int, int, int);
int u[60005];
int v[60005];
int w[60005];
int fi[30005];
int ne[60005];
int pe = 0;     //无向邻接表
int wp[30005];  //下放的点权
void dfs1(int);
int fa[30005];    //父亲
int dep[30005];   //深度
int size[30005];  //子树大小
int son[30005];   //重儿子
void dfs2(int);
int top[30005];   //链顶节点
int dfsx[30005];  // dfs序
int xu = 0;
int pos[30005];  //节点位置,in Sgt.
struct rg_a {
  ll yh;                              //异或和
  ll ans;                             //答案
  ll p0[10], p1[10], s0[10], s1[10];  //本段区间二进制第j位为0/1的前/后缀区间数
  inline void merge(rg_a &A, rg_a &B) {  //合并
    rg_a T;                              //记录合并结果
    int bl, br;  //抽取A/B的异或和的二进制第i位
    T.yh = A.yh ^ B.yh;
    T.ans = A.ans + B.ans;
    for (ri i = 0; i < 10; i++) {
      T.ans += A.s0[i] * B.p1[i] * (1 << i);
      T.ans += A.s1[i] * B.p0[i] * (1 << i);
      bl = (A.yh >> i) & 1;
      br = (B.yh >> i) & 1;
      T.p0[i] = A.p0[i];
      if (bl)
        T.p0[i] += B.p1[i];
      else
        T.p0[i] += B.p0[i];
      T.p1[i] = A.p1[i];
      if (bl)
        T.p1[i] += B.p0[i];
      else
        T.p1[i] += B.p1[i];
      T.s0[i] = B.s0[i];
      if (br)
        T.s0[i] += A.s1[i];
      else
        T.s0[i] += A.s0[i];
      T.s1[i] = B.s1[i];
      if (br)
        T.s1[i] += A.s0[i];
      else
        T.s1[i] += A.s1[i];
    }
    *this = T;
  }
};
struct sgt {  //线段树
  rg_a node[120005];
  void build(int o, int l, int r) {
    if (l == r) {
      node[o].yh = node[o].ans = wp[dfsx[l]];
      for (ri i = 0; i < 10; i++) {
        node[o].p0[i] = node[o].s0[i] = ((node[o].yh >> i) & 1) ^ 1;
        node[o].p1[i] = node[o].s1[i] = (node[o].yh >> i) & 1;
      }
    } else {
      build(lson, l, mid);
      build(rson, mid + 1, r);
      node[o].merge(node[lson], node[rson]);
    }
  }
  void update(int o, int l, int r, int p, int x) {
    if (l == r && l == p) {
      node[o].yh = node[o].ans = x;
      for (ri i = 0; i < 10; i++) {
        node[o].p0[i] = node[o].s0[i] = ((x >> i) & 1) ^ 1;
        node[o].p1[i] = node[o].s1[i] = (x >> i) & 1;
      }
    } else {
      if (p <= mid)
        update(lson, l, mid, p, x);
      else
        update(rson, mid + 1, r, p, x);
      node[o].merge(node[lson], node[rson]);
    }
  }
  rg_a query(int o, int l, int r, int a, int b) {
    if (l >= a && r <= b)
      return node[o];
    else {
      if (b <= mid)
        return query(lson, l, mid, a, b);
      else if (a > mid)
        return query(rson, mid + 1, r, a, b);
      else {
        rg_a tl = query(lson, l, mid, a, b);
        rg_a tr = query(rson, mid + 1, r, a, b);
        tl.merge(tl, tr);
        return tl;
      }
    }
  }
} tree;
inline ll path_query(int, int);
rg_a TL[50], TR[50];  //外层查询临时结果
int pl, pr;           //记录TL和TR存放的临时结果的数量
int n, q;
int f, x, y, z;
int root;
int main() {
  srand(time(0) + 19260817);
  read(n);
  read(q);
  root = rand() % n + 1;  // Ha~
  for (ri i = 1; i < n; i++) {
    read(x);
    read(y);
    read(z);
    addedge(x, y, z);
    addedge(y, x, z);
  }
  fa[root] = 0;
  dep[root] = 1;
  wp[root] = 0;
  dfs1(root);
  top[root] = root;
  dfs2(root);
  for (ri i = 1; i <= n; i++) pos[dfsx[i]] = i;
  tree.build(1, 1, n);
  while (q--) {
    read(f);
    if (f == 1) {
      read(x);
      read(y);
      printf("%lld\n", path_query(x, y));
    } else {
      read(x);
      read(y);
      read(z);
      if (pos[x] < pos[y])
        tree.update(1, 1, n, pos[y], z);
      else
        tree.update(1, 1, n, pos[x], z);
    }
  }
  return 0;
}
inline void addedge(int x, int y, int z) {
  pe++;
  u[pe] = x;
  v[pe] = y;
  w[pe] = z;
  ne[pe] = fi[x];
  fi[x] = pe;
}
void dfs1(int s) {
  size[s] = 1;
  int maxson = 0;
  int t = fi[s];
  int to = v[t];
  while (t) {
    if (to != fa[s]) {
      fa[to] = s;
      dep[to] = dep[s] + 1;
      wp[to] = w[t];
      dfs1(to);
      size[s] += size[to];
      if (size[to] > maxson) {
        son[s] = to;
        maxson = size[to];
      }
    }
    t = ne[t];
    to = v[t];
  }
}
void dfs2(int s) {
  xu++;
  dfsx[xu] = s;
  if (son[s]) {
    top[son[s]] = top[s];
    dfs2(son[s]);
  }
  int t = fi[s];
  int to = v[t];
  while (t) {
    if (to != fa[s] && to != son[s]) {
      top[to] = to;
      dfs2(to);
    }
    t = ne[t];
    to = v[t];
  }
}
inline ll path_query(int x, int y) {
  if (x == y) return 0;  //特判起终点相同
  pl = pr = 0;           //重置临时结果数组
  int tx = top[x], ty = top[y];
  while (tx != ty) {
    if (dep[tx] > dep[ty]) {
      pl++;
      TL[pl] = tree.query(1, 1, n, pos[tx], pos[x]);
      x = fa[tx];
      tx = top[x];
    } else {
      pr++;
      TR[pr] = tree.query(1, 1, n, pos[ty], pos[y]);
      y = fa[ty];
      ty = top[y];
    }
  }
  if (x != y) {
    if (pos[x] < pos[y]) {
      pr++;
      TR[pr] = tree.query(1, 1, n, pos[x] + 1, pos[y]);
    } else {
      pl++;
      TL[pl] = tree.query(1, 1, n, pos[y] + 1, pos[x]);
    }
  }
  for (ri i = 2; i <= pl; i++) TL[1].merge(TL[i], TL[1]);
  for (ri i = 2; i <= pr; i++) TR[1].merge(TR[i], TR[1]);
  //这里全部都要注意运算顺序！
  if (!pl)
    return TR[1].ans;
  else if (!pr)
    return TL[1].ans;  //特判答案仅在lca一侧的情况
  else {
    for (ri i = 0; i < 10; i++) {
      swap(TL[1].p0[i], TL[1].s0[i]);
      swap(TL[1].p1[i], TL[1].s1[i]);
    }  //“翻转”TL[1]
    TL[1].merge(TL[1], TR[1]);
    return TL[1].ans;
  }
}