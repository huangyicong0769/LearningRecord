#include <cmath>
#include <cstdio>
#include <iostream>
#include <set>
#define SIZE 100006
#define il inline
#define reg register
#define f(i, s, t, d) for (reg int i = s; i != t; i += d)
using namespace std;

multiset<pair<int, int> > ms;
multiset<pair<int, int> >::iterator it, it1, it2, it3, it4;

const int INF = 0x3F3F3F3F;
int N, M, X, W, la, lb, H[SIZE], ga[SIZE], gb[SIZE], f[18][SIZE][2],
    da[18][SIZE][2], db[18][SIZE][2];

il void cal(const int &S, const int &X) {
  la = lb = 0;
  reg int p = S;
  f(i, W, -1, -1) if (f[i][p][0] && la + lb + da[i][p][0] + db[i][p][0] <= X)
      la += da[i][p][0],
      lb += db[i][p][0], 
      p = f[i][p][0];
}

int main() {
  scanf("%d", &N);
  f(i, 1, N + 1, 1) scanf("%d", &H[i]);
  W = log(N) / log(2);
  ms.insert(make_pair(INF, 0));
  ms.insert(make_pair(INF, 0));
  ms.insert(make_pair(-INF, 0));
  ms.insert(make_pair(-INF, 0));
  f(i, N, -1, -1) {
    ms.insert(make_pair(H[i], i));
    it = ms.find(make_pair(H[i], i));
    it1 = (++it);
    it2 = (++it);
    it3 = (--(--(--it)));
    it4 = (--it);
    reg int a = (*it3).first == -INF ? INF : H[i] - (*it3).first,
            b = (*it1).first == INF ? INF : (*it1).first - H[i];
    if (a <= b) {
      gb[i] = (*it3).second;
      a = (*it4).first == -INF ? INF : H[i] - (*it4).first,
      ga[i] = a <= b ? (*it4).second : (*it1).second;
    } else {
      gb[i] = (*it1).second;
      b = (*it2).first == INF ? INF : (*it2).first - H[i];
      ga[i] = a <= b ? (*it3).second : (*it2).second;
    }
  }
  f(j, 1, N + 1, 1) f[0][j][0] = ga[j], f[0][j][1] = gb[j];
  f(j, 1, N + 1, 1) f[1][j][0] = f[0][f[0][j][0]][1],
                    f[1][j][1] = f[0][f[0][j][1]][0];
  f(i, 2, W, 1) f(j, 1, N + 1, 1) f[i][j][0] = f[i - 1][f[i - 1][j][0]][0],
                                  f[i][j][1] = f[i - 1][f[i - 1][j][1]][1];
  f(j, 1, N + 1, 1) da[0][j][0] = abs(H[j] - H[ga[j]]),
                    db[0][j][1] = abs(H[j] - H[gb[j]]),
                    da[0][j][1] = db[0][j][0] = 0;
  f(j, 1, N + 1, 1) da[1][j][0] = da[0][j][0] + da[0][f[0][j][0]][1],
                    da[1][j][1] = da[0][j][1] + da[0][f[0][j][1]][0],
                    db[1][j][0] = db[0][j][0] + db[0][f[0][j][0]][1],
                    db[1][j][1] = db[0][j][1] + db[0][f[0][j][1]][0];
  f(i, 2, W, 1) f(j, 1, N + 1, 1)
      da[i][j][0] = da[i - 1][j][0] + da[i - 1][f[i - 1][j][0]][0],
      da[i][j][1] = da[i - 1][j][1] + da[i - 1][f[i - 1][j][1]][1],
      db[i][j][0] = db[i - 1][j][0] + db[i - 1][f[i - 1][j][0]][0],
      db[i][j][1] = db[i - 1][j][1] + db[i - 1][f[i - 1][j][1]][1];
  scanf("%d", &X);
  cal(1, X);
  reg double ans[2] = {1, lb ? (double)la / lb : INF};
  f(i, 2, N + 1, 1) {
    cal(i, X);
    reg double tmp = (double)la / lb;
    if (tmp < ans[1] || tmp == ans[1] && H[i] > H[(int)ans[0]])
      ans[0] = i, ans[1] = tmp;
  }
  printf("%.0lf\n", ans[0]);
  scanf("%d", &M);
  f(i, 0, M, 1) {
    reg int s, x;
    scanf("%d%d", &s, &x);
    cal(s, x);
    printf("%d %d\n", la, lb);
  }
}