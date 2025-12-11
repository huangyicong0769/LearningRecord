#include <iostream>
#include <vector>
#include <map>
using namespace std;

class Solution {
    int gcd (int a, int b){
        // cout << a << " " << b << endl;
        if (a < b) return gcd(b, a);
        return b == 0 ? a : gcd(b, a % b);
    }

    pair<int, int> regular(pair<int, int> p){
        auto [a, b] = p;
        int flag = 1;
        if (a < 0) {flag *= -1; a *= -1;};
        if (b < 0) {flag *= -1; b *= -1;};
        return {flag*a, b};
    }

    int encode(int a, int b){
        int flag = 1;
        if (a < 0) {flag *= -1; a *= -1;};
        if (b < 0) {flag *= -1; b *= -1;};
        if (a == 0 || b == 0) flag = 1;
        return flag*(a * 10000 + b);
    }

    pair<int, int> decode(int c){
        int flag = 1;
        if (c < 0) {flag *= -1; c *= -1;};
        return {flag * (c / 10000), c % 10000};
    }

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

    int dist2(const vector<int> &p1, const vector<int> &p2){
        return (p1[0] - p2[0]) * (p1[0] - p2[0]) + (p1[1] - p2[1]) * (p1[1] - p2[1]);
    }

public:
    int countTrapezoids(vector<vector<int>>&& points) {
        std::sort(points.begin(), points.end(), [](const vector<int> &a, const vector<int> &b) -> bool {
            return a[0] < b[0] || a[0] == b[0] && a[1] < b[1];
        });
        std::unordered_map<int, vector<pair<vector<int>&, vector<int>&>>> m;
        for (int i = 0; i < points.size(); i++)
            for (int j = i + 1; j < points.size(); j++){
                // cout << "!" << endl;
                int dy = points[j][1] - points[i][1],
                    dx = points[j][0] - points[i][0],
                    g = gcd(abs(dy), abs(dx));
                m[encode(dy/g, dx/g)].push_back({points[i], points[j]});
            }
        int ans = 0, cnt = 0;
        for (auto & [d, v]:m){
            for (int i = 0; i < v.size(); i++)
                for (int j = i + 1; j < v.size(); j++){
                    auto [dy, dx] = regular({v[j].first[1] - v[i].second[1], v[j].first[0] - v[i].second[0]});
                    if (dx == 0 && dy == 0) continue;
                    int g = gcd(abs(dy), dx);
                    dy /= g; dx /= g;
                    if (d == encode(dy, dx)) continue;
                    ans++;
                    if (dist2(v[i].first, v[i].second) == dist2(v[j].first, v[j].second))
                        cnt++;
                    // cout << d << ", " << encode(dy, dx) << endl;
                    // printPointPair(v[i]); cout << ", ";
                    // printPointPair(v[j]); cout << endl;
                }
        }
        return ans - cnt/2;
    }
};

int main(){
    Solution a;
    cout << a.countTrapezoids({{71,-89},{-75,-89},{-9,11},{-24,-89},{-51,-89},{-77,-89},{42,11}}) << endl;
}