#include <algorithm>
#include <cmath>
#include <cstdio>
#include <initializer_list>
#include <iomanip>
#include <iostream>
using namespace std;
#define reg register
#define f(i, s, t) for (reg int i = s; i <= t; i++)

class Vector {
 public:
  double x, y;
  Vector() { x = y = 0; }

  Vector(const double &x, const double &y) { this->x = x, this->y = y; }

  Vector(initializer_list<double> a) {
    this->x = *a.begin(), this->y = *(a.begin() + 1);
  }

  Vector(const Vector &v) { *this = v; }

  inline double mode() { return sqrt(x * x + y * y); }

  inline Vector opp(const Vector &v) { return {-v.x, -v.y}; }

  inline Vector add(const Vector &v) { return {this->x + v.x, this->y + v.y}; }

  inline Vector dec(const Vector &v) { return this->add(opp(v)); }

  inline Vector mul(const double &k) { return {this->x * k, this->y * k}; }

  inline double dot(const Vector &v) { return this->x * v.x + this->y * v.y; }

  inline double out(const Vector &v) { return this->x * v.y - v.x * this->y; }

  inline bool ver(const Vector &v) { return this->dot(v) == 0; }

  inline bool col(const Vector &v) { return *this * v == 0; }

  inline Vector rot(const double &th) {
    return {(x * cos(th) - y * sin(th)), (y * cos(th) + x * sin(th))};
  }

  inline Vector operator+(const Vector &v) { return this->add(v); }

  inline Vector operator-(const Vector &v) { return this->dec(v); }

  inline Vector operator*(const double &k) { return this->mul(k); }

  inline double operator*(const Vector &v) { return this->out(v); }

  inline friend istream &operator>>(istream &in, Vector &v) {
    in >> v.x >> v.y;
    if (!in) v = Vector();
    return in;
  }

  inline friend ostream &operator<<(ostream &out, const Vector &v) {
    out.setf(ios::fixed);
    out << fixed << setprecision(2) << "(" << v.x << ", " << v.y << ")";
    return out;
  }

  inline bool operator==(const Vector &v) {
    return this->x == v.x && this->y == v.y;
  }

  inline bool operator<(const Vector &v) {
    return this->x < v.x || this->x == v.x && this->y < v.y;
  }

  inline bool operator<=(const Vector &v) { return *this < v || *this == v; }

  inline bool operator>(const Vector &v) { return !(*this <= v); }

  inline bool operator>=(const Vector &v) { return *this > v || *this == v; }

  inline bool operator!=(const Vector &v) { return !(*this == v); }
};
typedef Vector Point;

const int SN = 10006;
int N, h[SN];
Point a[SN];

inline int convexHull() {
  sort(a + 1, a + 1 + N);
  reg int top = 0;
  bool used[SN] = {0};
  h[++top] = 1;
  f(i, 2, N) {
    if (used[i]) continue;
    while (top > 1 && (a[h[top]] - a[h[top - 1]]) * (a[i] - a[h[top]]) <= 0)
      used[h[top--]] = 0;
    used[i] = 1, h[++top] = i;
  }
  reg int k = top;
  for (reg int i = N - 1; i; i--) {
    if (used[i]) continue;
    while (top > k && (a[h[top]] - a[h[top - 1]]) * (a[i] - a[h[top]]) <= 0)
      used[h[top--]] = 0;
    used[i] = 1, h[++top] = i;
  }
  // f(i, 1, top) cout << a[h[i]] << endl;
  return top;
}

int main() {
  scanf("%d\n", &N);
  f(i, 1, N) cin >> a[i];
  reg double ans = 0, cnt = convexHull();
  f(i, 2, cnt) ans += (a[h[i]] - a[h[i - 1]]).mode();
  printf("%.2lf\n", ans);
}