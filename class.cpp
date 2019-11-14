#include <bits/stdc++.h>
using namespace std;

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

class KMP {
  char *cs;
  vector<int> nxt;

  inline void init() {
    int m = strlen(cs + 1);
    nxt.resize(m + 1);
    for (int i = 2, j = 0; i <= m; i++) {
      while (j && cs[i] != cs[j + 1]) j = nxt[j];
      if (cs[i] == cs[j + 1]) j++;
      nxt[i] = j;
    }
  }

 public:
  KMP(char *s) { cs = s, init(); }

  inline void find(char *s) {
    int m = strlen(cs + 1), n = strlen(s + 1);
    for (int i = 1, j = 0; i <= n; i++) {
      while (j && s[i] != cs[j + 1]) j = nxt[j];
      if (s[i] == cs[j + 1]) j++;
      if (j == m) {
        printf("%d\n", i - m + 1);
        j = nxt[j];
      }
    }
  }

  inline void printNxt() {
    int m = strlen(cs + 1);
    for (int i = 1; i <= m; i++) printf("%d ", nxt[i]);
    puts("");
  }
};