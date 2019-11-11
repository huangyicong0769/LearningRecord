#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
using namespace std;
#define reg register
#define f(i, s, t) for (reg int i = s; i <= t; i++)
#define ms(a, b) memset(a, b, sizeof(a))
#define il inline
typedef long long ll;

const int Bits = 8, SN = 1506;
const ll base = 1e8;
class BigNum {
  ll v[SN];
  int len;

 public:
  BigNum() { ms(v, 0), len = 0; }
  BigNum(string s) {
    reverse(s.begin(), s.end());
    ms(v, 0), len = 0;
    reg int slen = s.length();
    len = 0;
    for (reg int i = 0, w = 0; i < slen; i++, w *= 10) {
      if (i % Bits == 0) len++, w = 1;
      v[len] += w * (s[i] - '0');
    }
  }
  il void print() {
    printf("%lld", v[len]);
    for (reg int i = len - 1; i; i--) {
      for (reg int k = base / 10; v[i] < k; k /= 10) putchar('0');
      if (v[i]) printf("%lld", v[i]);
    }
    puts("");
  }
  il bool operator<(const BigNum &a) {
    if (this->len < a.len) return 1;
    if (this->len > a.len) return 0;
    for (reg int i = len; i; i--)
      if (this->v[i] != a.v[i]) return this->v[i] < a.v[i];
  }
  il BigNum operator-(reg BigNum a) {
    reg BigNum ans = *this;
    if (ans < a) swap(ans, a);
    f(i, 1, ans.len) if ((ans.v[i] -= a.v[i]) < 0) ans.v[i] += base,
        --ans.v[i + 1];
    while (ans.len > 0 && !ans.v[ans.len]) ans.len--;
    return ans;
  }
  il BigNum operator/(int a) {
    reg BigNum ans = *this;
    for (reg int i = ans.len; i > 1; i--) {
      ans.v[i - 1] += (ans.v[i] & 1) * base;
      ans.v[i] >>= 1;
    }
    ans.v[1] >>= 1;
    while (ans.len > 0 && !ans.v[ans.len]) ans.len--;
    return ans;
  }
  il BigNum operator*(int a) {
    reg BigNum ans = *this;
    f(i, 1, ans.len) ans.v[i] <<= 1;
    f(i, 1, ans.len + 1) ans.v[i + 1] += ans.v[i] / base, ans.v[i] %= base;
    while (ans.len <= SN && ans.v[ans.len + 1]) ans.len++;
    return ans;
  }
  il bool even(){
    return v[1]%2 == 0;
  }
}one("1"), zero("0");

BigNum gcd(BigNum a, BigNum b) {
  reg int cnt = 0;
  while (1) {
    if (a < one) break;
    if (a.even() && b.even()) {
      cnt++, a = a / 2, b = b / 2;
      continue;
    }
    if (a.even()) {
      a = a / 2;
      continue;
    }
    if (b.even()) {
      b = b / 2;
      continue;
    }
    reg BigNum tmp = a;
    a = a < b ? b - a : a - b;
    b = tmp < b ? tmp : b;
  }
  while (cnt) {
    b = b * 2, cnt--;
  }
  return b;
}

int main() {
  string s1, s2;
  cin >> s1 >> s2;
  BigNum a(s1), b(s2);
  gcd(a, b).print();
}