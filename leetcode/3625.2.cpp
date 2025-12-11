#include <iostream>
#include <vector>
#include <map>

#include <numeric>
#include <functional>
#include <stdexcept>
#include <cstdint>

using namespace std;

class Rational {
    int gcd (int a, int b){
        // cout << a << " " << b << endl;
        if (a < b) return gcd(b, a);
        return b == 0 ? a : gcd(b, a % b);
    }
public:
    int num; // numerator
    int den; // denominator (0 => +infinity)

    Rational(int n = 0, int d = 1) : num(n), den(d) {
        normalize();
    }

    // 是否是 +∞
    bool isInf() const {
        return den == 0;
    }

    // 约分 + 规范化
    void normalize() {
        // Infinity: 统一为 <1,0>
        if (den == 0) {
            num = 1;
            return;
        }

        // 0 统一为 0/1
        if (num == 0) {
            den = 1;
            return;
        }

        // 确保分母为正，把符号放到分子上
        if (den < 0) {
            num = -num;
            den = -den;
        }

        int g = gcd(abs(num), abs(den));
        num /= g;
        den /= g;
    }

    // 相等比较（给 unordered_map 用）
    bool operator==(const Rational &other) const {
        return num == other.num && den == other.den;
    }

    // 严格小于（可选，用于排序）
    bool operator<(const Rational &other) const {
        // +∞ 比较
        if (isInf() && other.isInf()) return false;
        if (isInf()) return false;           // +∞ 最大
        if (other.isInf()) return true;

        return num * other.den < other.num * den;
    }

    // 一元负号
    Rational operator-() const {
        if (isInf()) {
            // 没有负无穷，只能认为非法
            throw std::overflow_error("Negation of +infinity is not supported");
        }
        return Rational(-num, den);
    }

    // 加法
    Rational operator+(const Rational &other) const {
        // 处理无穷
        if (isInf() || other.isInf()) {
            if (isInf() && other.isInf()) {
                // +∞ + +∞ = +∞
                return Rational(1, 0);
            }
            // 有一个是 +∞，另一个有限：结果仍为 +∞
            return Rational(1, 0);
        }

        // (a/b) + (c/d) = (ad + bc) / bd
        int n = num * other.den + other.num * den;
        int d = den * other.den;

        // 简单处理：强转回 long long，实际项目中可以加溢出检查
        return Rational(n, d);
    }

    // 减法
    Rational operator-(const Rational &other) const {
        // a - b = a + (-b)
        if (other.isInf()) {
            if (isInf()) {
                // +∞ - +∞ 未定义
                throw std::overflow_error("+infinity - +infinity is undefined");
            }
            // 有限 - +∞ = -∞（本类不支持），直接报错
            throw std::overflow_error("finite - +infinity would be -infinity, unsupported");
        }
        if (isInf()) {
            // +∞ - 有限 = +∞
            return Rational(1, 0);
        }
        return *this + (-other);
    }

    // 乘法
    Rational operator*(const Rational &other) const {
        // 任一为 +∞
        if (isInf() || other.isInf()) {
            // 0 * ∞ 未定义
            if ((isInf() && other.num == 0) ||
                (other.isInf() && num == 0)) {
                throw std::overflow_error("0 * infinity is undefined");
            }

            // 有限 * +∞，看结果符号：
            // 如果结果应为负无穷，则我们不支持 -> 抛异常
            long long sign = 1;
            if (isInf()) sign *= (other.num > 0 ? 1 : -1);
            if (other.isInf()) sign *= (num > 0 ? 1 : -1);

            if (sign < 0) {
                throw std::overflow_error("Result would be -infinity, which is not supported");
            }
            // 结果为 +∞
            return Rational(1, 0);
        }

        int n = num * other.num;
        int d = den * other.den;
        return Rational(n, d);
    }

    // 除法
    Rational operator/(const Rational &other) const {
        // 除以 0（有限数）
        if (!other.isInf() && other.num == 0) {
            throw std::overflow_error("Division by zero");
        }

        // 本身有限，被除数有限
        if (!isInf() && !other.isInf()) {
            // (a/b) / (c/d) = (a*d) / (b*c)
            int n = num * other.den;
            int d = den * other.num;
            return Rational(n, d);
        }

        // this 是 +∞, other 是有限
        if (isInf() && !other.isInf()) {
            long long sign = (other.num > 0 ? 1 : -1);
            if (sign < 0) {
                // 结果为 -∞，不支持
                throw std::overflow_error("+infinity / negative would be -infinity, unsupported");
            }
            return Rational(1, 0); // +∞ / 正数 = +∞
        }

        // this 有限, other 是 +∞
        if (!isInf() && other.isInf()) {
            // 有限 / +∞ = 0
            return Rational(0, 1);
        }

        // +∞ / +∞ 未定义
        if (isInf() && other.isInf()) {
            throw std::overflow_error("infinity / infinity is undefined");
        }

        // 理论上不会到这里
        throw std::logic_error("Unreachable in Rational::operator/");
    }

    // 复合运算符（方便使用）
    Rational& operator+=(const Rational &other) { *this = *this + other; return *this; }
    Rational& operator-=(const Rational &other) { *this = *this - other; return *this; }
    Rational& operator*=(const Rational &other) { *this = *this * other; return *this; }
    Rational& operator/=(const Rational &other) { *this = *this / other; return *this; }
};

// Hash specialization for unordered_map
namespace std {
    template <>
    struct hash<Rational> {
        std::size_t operator()(const Rational &r) const noexcept {
            std::size_t h1 = std::hash<long long>()(r.num);
            std::size_t h2 = std::hash<long long>()(r.den);
            return h1 ^ (h2 + 0x9e3779b97f4a7c15ULL + (h1 << 6) + (h1 >> 2));
        }
    };
}


class Solution {
    void printPoint(const vector<int> &p){
        cout << "(" << p[0] << ", " << p[1] << ")";
    }

    void printPoint(const pair<int, int> &p){
        cout << "(" << p.first << ", " << p.second << ")";
    }

    void printPointPair(const pair<vector<int>&, vector<int>&> &pp){
        cout << "<";
        printPoint(pp.first);
        cout << ", ";
        printPoint(pp.second);
        cout << ">";
    }

    int dist2(const int &dx, const int &dy){
        return dx*dx + dy*dy;
    }

    int dist2(const vector<int> &p1, const vector<int> &p2){
        return dist2(p1[0] - p2[0], p1[1] - p2[1]);
    }

public:
    int countTrapezoids(vector<vector<int>>&& points) {
        // std::sort(points.begin(), points.end(), [](const vector<int> &a, const vector<int> &b) -> bool {
        //     return a[0] < b[0] || a[0] == b[0] && a[1] < b[1];
        // });
        std::unordered_map<Rational, std::unordered_map<Rational, std::unordered_map<int, int>>> m;
        for (int i = 0; i < points.size(); i++)
            for (int j = i + 1; j < points.size(); j++){
                // cout << i << j << endl;
                // printPointPair({points[i], points[j]}); cout << endl;
                // cout << "!" << endl;
                int dy = points[j][1] - points[i][1],
                    dx = points[j][0] - points[i][0],
                    l = dist2(dx, dy);
                if (dx == 0) {
                    m[Rational(1, 0)][points[i][0]][l]++;
                }else m[Rational(dy, dx)][Rational(dy * points[i][0] - dx * points[i][1], dx)][l]++;
            }
        int ans = 0, cnt = 0;
        for (auto & [k, v]:m){
            std::unordered_map<int, int> tm;
            int temp = 0;
            for (auto & [b, w]:v){
                for (auto & [l, s]:w){
                    ans += temp * s;
                    cnt += tm[l] * s;
                }
                for (auto & [l, s]:w){
                    temp += s;
                    tm[l] += s;
                }
            }
        }
        return ans - cnt/2;
    }
};

int main(){
    Solution a;
    cout << a.countTrapezoids({{71,-89},{-75,-89},{-9,11},{-24,-89},{-51,-89},{-77,-89},{42,11}}) << endl;
}