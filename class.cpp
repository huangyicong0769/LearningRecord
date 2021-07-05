#include <cmath>
#include <cstdio>
#include <initializer_list>
#include <iomanip>
#include <iostream>
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

  double mode() { return sqrt(x * x + y * y); }

  Vector opp(const Vector &v) { return {-v.x, -v.y}; }

  Vector add(const Vector &v) { return {this->x + v.x, this->y + v.y}; }

  Vector dec(const Vector &v) { return this->add(opp(v)); }

  Vector mul(const double &k) { return {this->x * k, this->y * k}; }

  double dot(const Vector &v) { return this->x * v.x + this->y * v.y; }

  double out(const Vector &v) { return this->x * v.y - v.x * this->y; }

  bool ver(const Vector &v) { return this->dot(v) == 0; }

  bool col(const Vector &v) { return *this * v == 0; }

  Vector rot(const double &th) {
    return {(x * cos(th) - y * sin(th)), (y * cos(th) + x * sin(th))};
  }

  Vector operator+(const Vector &v) { return this->add(v); }

  Vector operator-(const Vector &v) { return this->dec(v); }

  Vector operator*(const double &k) { return this->mul(k); }

  double operator*(const Vector &v) { return this->out(v); }

  friend istream &operator>>(istream &in, Vector &v) {
    in >> v.x >> v.y;
    if (!in) v = Vector();
    return in;
  }

  friend ostream &operator<<(ostream &out, const Vector &v) {
    out.setf(ios::fixed);
    out << fixed << setprecision(2) << "(" << v.x << ", " << v.y << ")";
    return out;
  }

  bool operator==(const Vector &v) {
    return this->x == v.x && this->y == v.y;
  }

  bool operator<(const Vector &v) {
    return this->x < v.x || this->x == v.x && this->y < v.y;
  }

  bool operator<=(const Vector &v) { return *this < v || *this == v; }

  bool operator>(const Vector &v) { return !(*this <= v); }

  bool operator>=(const Vector &v) { return *this > v || *this == v; }

  bool operator!=(const Vector &v) { return !(*this == v); }
};