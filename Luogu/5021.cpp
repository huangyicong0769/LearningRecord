#include <cstdio>
#include <cstring>
#include <iostream>
#include <set>
using namespace std;
#define rg register
#define reg rg int
#define f(i, s, t) for (reg i = s; i <= t; i++)
#define il inline

const int SN = 50006;

int tot, Head[SN], Next[SN << 1], Ver[SN << 1], Edge[SN << 1], N, M, cnt,
    dep[SN], td;

il void add(int x, int y, int z) {
  Ver[++tot] = y, Edge[tot] = z, Next[tot] = Head[x], Head[x] = tot;
}

void dfs0(int x, int fa) {
  for (reg i = Head[x]; i; i = Next[i]) {
    reg y = Ver[i];
    if (y == fa) continue;
    dfs0(y, x);
    td = max(td, dep[x] + dep[y] + Edge[i]);
    dep[x] = max(dep[x], dep[y] + Edge[i]);
  }
}

multiset<int> ms[SN];
int dfs(int x, int fa, int k) {
  ms[x].clear();
  // cout << x << ' ' << fa << ' ' << k << endl;
  for (reg i = Head[x]; i; i = Next[i]) {
    reg y = Ver[i];
    if (y == fa) continue;
    reg val = dfs(y, x, k) + Edge[i];
    if (val >= k)
      cnt++;
    else
      ms[x].insert(val);
  }
  // cout << x << "!" << endl;
  reg ret = 0;
  for (rg multiset<int>::iterator it2; !ms[x].empty();) {
#define it ms[x].begin()
    // cout << "  1" << endl;
    if (ms[x].size() == 1) return max(ret, *it);
    // cout << "  2" << endl;
    it2 = ms[x].lower_bound(k - *it);
    if (it2 == it && ms[x].count(*it2) == 1) it2++;
    // cout << "  3" << endl;
    if (it2 == ms[x].end())
      ret = max(ret, *it), ms[x].erase(ms[x].find(*it));
    else
      cnt++, ms[x].erase(ms[x].find(*it)), ms[x].erase(ms[x].find(*it2));
    // cout << "  4" << endl;
#undef it
  }
  return ret;
}

il bool check(int k) {
  cnt = 0;
  dfs(1, -1, k);
  // cout << "#" << ans << endl;
  return cnt >= M;
}

int main() {
  freopen("input.txt", "r", stdin);
  // freopen("output.txt", "w", stdout);
  scanf("%d%d", &N, &M);
  f(i, 2, N) {
    reg a, b, l;
    scanf("%d%d%d", &a, &b, &l);
    add(a, b, l), add(b, a, l);
  }
  td = 0, dfs0(1, -1);
  reg l = 0, r = td, ans;
  while (l <= r) {
    // cout << l << ' ' << r << endl;
    reg mid = (l + r) >> 1;
    if (check(mid))
      ans = mid, l = mid + 1;
    else
      r = mid - 1;
  }
  printf("%d\n", ans);
}