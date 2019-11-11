#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;
#define reg register int
#define f(i, s, t) for (reg i=s; i<=t; i++)
#define il inline

const int SN = 1e5+6;

class Treap{
 public:
  int v[SN], w[SN], si[SN], son[SN][2], tot;
  bool fl[SN];
  Treap(){
    tot = 0;
  }
  il int newPoint(const int &value){
    v[++tot] = value, w[tot] = rand(), si[tot] = 1;
    return tot;
  }
  il void update(const int &pos){
    si[pos] = si[son[pos][0]] + si[son[pos][1]] + 1;
  }
  il void push(const int &pos){
    swap(son[pos][0], son[pos][1]);
    if (son[pos][0]) fl[son[pos][0]] ^= 1;
    if (son[pos][1]) fl[son[pos][1]] ^= 1;
    fl[pos] = 0;
  }
  void split(int now, int k, int &l, int &r){
    if (!now){
      l = r = 0;
      return;
    }
    if (fl[now]) push(now); 
    if (si[son[now][0]]<k)
      l = now, split(son[now][1], k - si[son[now][0]] - 1, son[now][1], r);
    else
      r = now, split(son[now][0], k, l, son[now][0]);
    update(now);
  }
  int merge(int l, int r){
    if (!l || !r) return l + r;
    if (w[l] < w[r]) {
      if (fl[l]) push(l);
      son[l][1] = merge(son[l][1], r);
      update(l);
      return l;
    }else{
      if (fl[r]) push(r);
      son[r][0] = merge(l, son[r][0]);
      update(r); 
      return r;
    }
  }
  void out(int pos){
    if (!pos) return;
    if (fl[pos]) push(pos);
    out(son[pos][0]);
    printf("%d ", v[pos]);
    out(son[pos][1]);
  }
}tr;

int main(){
  reg N, M, root = 0;
  scanf("%d%d", &N, &M);
  f(i, 1, N) root=tr.merge(root, tr.newPoint(i));
  f(i, 1, M){
    reg l, r, r1, r2, r3;
    scanf("%d%d", &l, &r);
    tr.split(root, l - 1, r1, r2);
    tr.split(r2, r - l + 1, r2, r3);
    tr.fl[r2] ^= 1;
    root = tr.merge(r1, tr.merge(r2, r3));
  }
  tr.out(root), puts("");
}