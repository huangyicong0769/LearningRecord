#include <bits/stdc++.h>
using namespace std;
const int maxm = 105;
int i;
int gcd(int a, int b) {
  if (b == 0) return a;
  return gcd(b, a % b);
}
void tomin(double &a, double b) { a > b ? a = b : 0; }  //取最小值的函数
struct point {
  // sum是运动周期 , to 是此时点所在线段,now是在此线段运动的时间
  double x, y;
  int m, sum, to, d[maxm], dir[maxm], now;
  char c[maxm];
  void read() {
    cin >> x >> y >> m;
    for (int i = 0; i < m; i++) {
      cin >> d[i] >> c[i];
      if (d[i] < 0)
        dir[i] = -1;
      else
        dir[i] = 1;
      d[i] = abs(d[i]);
      sum += d[i];
    }
  }
  void walk() {
    if (c[to] == 'X') {
      x = x + dir[to];
    } else
      y = y + dir[to];
    now++;
  }
  void update() {
    //当点的now 已经超出线段长度，更新线段
    if (now >= d[to]) {
      to = (to + 1) % m;
      now = 0;
    }
  }
};
double dis(point a, point b) {
  //求出a,b点的距离
  return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
int main() {
  point a, b;
  //取消读写同步,否则cin会超时
  ios::sync_with_stdio(false);
  a.read();
  b.read();
  double ans = dis(a, b);
  int t = a.sum * b.sum / gcd(a.sum, b.sum);
  //用前文思路 : 求出两点周期的最小公倍数
  for (i = 0; i <= t; i++) {
    //不断运动并更新
    a.walk();
    b.walk();
    a.update();
    b.update();
    tomin(ans, dis(a, b));  //更新取最小值
  }
  printf("%.2lf", ans);
  return 0;
}