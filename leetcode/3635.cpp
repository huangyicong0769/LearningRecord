#include "lc.hpp"

class Solution {
public:
    int earliestFinishTime(vector<int>& ls, vector<int>& ld, vector<int>& ws, vector<int>& wd) {
        std::vector<int> l(ls.size()), w(ws.size());
        for (int i = 0; i < l.size(); i++)
            l[i] = i;
        for (int i = 0; i < w.size(); i++)
            w[i] = i;
        std::sort(l.begin(), l.end(), [&](const int &a, const int &b){
            return ls[a] + ld[a] < ls[b] + ld[b] || ls[a] + ld[a] == ls[b] + ld[b] && ls[a] < ls[b];
        });
        std::sort(w.begin(), w.end(), [&](const int &a, const int &b){
            return ws[a] + wd[a] < ws[b] + wd[b] || ws[a] + wd[a] == ws[b] + wd[b] && ws[a] < ws[b];
        });
        int ans = 1e6, front = 1e6;
        for (int i = 0, j = -1; i < l.size(); i++){
            while (j + 1 < w.size() && ws[w[j + 1]] <= ls[l[i]] + ld[l[i]]){
                front = std::min(front, wd[w[++j]]);
            }
            if (j + 1 < w.size())
                ans = std::min(ans, ws[w[j + 1]] + wd[w[j + 1]]);
            ans = std::min(ans, ls[l[i]] + ld[l[i]] + front);
        }
        front = 1e6;
        for (int i = 0, j = -1; i < w.size(); i++){
            while (j + 1 < l.size() && ls[l[j + 1]] <= ws[w[i]] + wd[w[i]]){
                front = std::min(front, ld[l[++j]]);
            }
            if (j + 1 < l.size())
                ans = std::min(ans, ls[l[j + 1]] + ld[l[j + 1]]);
            ans = std::min(ans, ws[w[i]] + wd[w[i]] + front);
        }
        return ans;
    }
};

class Solution2 {
public:
    int earliestFinishTime(vector<int>& ls, vector<int>& ld, vector<int>& ws, vector<int>& wd) {
        const int inf = 1e9;
        auto ord = [&](const vector<int>& s, const vector<int>& d) {
            vector<int> p(s.size());
            iota(p.begin(), p.end(), 0);
            sort(p.begin(), p.end(), [&](int x, int y) {
                return s[x] + d[x] < s[y] + d[y] || s[x] + d[x] == s[y] + d[y] && s[x] < s[y];
            });
            return p;
        };
        vector<int> l = ord(ls, ld), w = ord(ws, wd);
        auto work = [&](const vector<int>& s1, const vector<int>& d1, const vector<int>& a,
                        const vector<int>& s2, const vector<int>& d2, const vector<int>& b) {
            int res = inf, mn = inf;
            for (int i = 0, j = -1; i < a.size(); i++) {
                int t = s1[a[i]] + d1[a[i]];
                while (j + 1 < b.size() && s2[b[j + 1]] <= t)
                    mn = min(mn, d2[b[++j]]);
                if (j + 1 < b.size())
                    res = min(res, s2[b[j + 1]] + d2[b[j + 1]]);
                if (mn < inf)
                    res = min(res, t + mn);
            }
            return res;
        };
        return min(work(ls, ld, l, ws, wd, w), work(ws, wd, w, ls, ld, l));
    }
};

class Solution3 {
public:
    int earliestFinishTime(vector<int>& ls, vector<int>& ld, vector<int>& ws, vector<int>& wd) {
        auto solver = [](const vector<int>& ls, const vector<int>& ld, const vector<int>& ws, const vector<int>& wd){
            int f1 = 1e6;
            for (int i = 0; i < ls.size(); i++)
                f1 = min(f1, ls[i] + ld[i]);
            int ans = 1e6;
            for (int i = 0; i < ws.size(); i++){
                if (ws[i] <= f1)
                    ans = min(ans, f1 + wd[i]);
                else
                    ans = min(ans, ws[i] + wd[i]);
            }
            return ans;
        };
        return min(solver(ls, ld, ws, wd), solver(ws, wd, ls, ld));
    }
};