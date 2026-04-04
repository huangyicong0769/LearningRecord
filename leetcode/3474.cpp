#include "lc.hpp"
#include <array>
#include <bitset>

class Solver3474 {
    static constexpr int MAXM = 500;

public:
    string solve(const string& str1, const string& str2) {
        int n = static_cast<int>(str1.size());
        int m = static_cast<int>(str2.size());
        int L = n + m - 1;

        vector<int> need(L, -1);
        for (int i = 0; i < n; ++i) {
            need[i + m - 1] = (str1[i] == 'T') ? 1 : 0;
        }

        vector<int> pi(m, 0);
        for (int i = 1; i < m; ++i) {
            int j = pi[i - 1];
            while (j > 0 && str2[i] != str2[j]) {
                j = pi[j - 1];
            }
            if (str2[i] == str2[j]) {
                ++j;
            }
            pi[i] = j;
        }

        vector<array<int, 26>> nxt(m);
        vector<array<unsigned char, 26>> hit(m);
        vector<bitset<MAXM>> reachAny(m), reachMiss(m), reachHit(m);

        for (int state = 0; state < m; ++state) {
            for (int c = 0; c < 26; ++c) {
                int k = state;
                char ch = static_cast<char>('a' + c);
                while (k > 0 && str2[k] != ch) {
                    k = pi[k - 1];
                }
                if (str2[k] == ch) {
                    ++k;
                }

                unsigned char matched = 0;
                if (k == m) {
                    matched = 1;
                    k = pi[m - 1];
                }

                nxt[state][c] = k;
                hit[state][c] = matched;
                reachAny[state].set(k);
                if (matched) {
                    reachHit[state].set(k);
                } else {
                    reachMiss[state].set(k);
                }
            }
        }

        vector<bitset<MAXM>> can(L + 1);
        for (int state = 0; state < m; ++state) {
            can[L].set(state);
        }

        for (int pos = L - 1; pos >= 0; --pos) {
            const bitset<MAXM>& nextRow = can[pos + 1];
            for (int state = 0; state < m; ++state) {
                const bitset<MAXM>* reach = &reachAny[state];
                if (need[pos] == 0) {
                    reach = &reachMiss[state];
                } else if (need[pos] == 1) {
                    reach = &reachHit[state];
                }
                if ((nextRow & *reach).any()) {
                    can[pos].set(state);
                }
            }
        }

        if (!can[0].test(0)) {
            return "";
        }

        string ans;
        ans.reserve(L);
        int state = 0;
        for (int pos = 0; pos < L; ++pos) {
            for (int c = 0; c < 26; ++c) {
                if (need[pos] != -1 && static_cast<int>(hit[state][c]) != need[pos]) {
                    continue;
                }
                int ns = nxt[state][c];
                if (can[pos + 1].test(ns)) {
                    ans.push_back(static_cast<char>('a' + c));
                    state = ns;
                    break;
                }
            }
        }

        return ans;
    }
};

class Solver3474Greedy {
public:
    string solve(const string& str1, const string& str2) {
        int n = static_cast<int>(str1.size());
        int m = static_cast<int>(str2.size());
        int L = n + m - 1;

        string ans(L, '?');
        vector<unsigned char> fixed(L, 0);

        for (int i = 0; i < n; ++i) {
            if (str1[i] != 'T') {
                continue;
            }
            for (int j = 0; j < m; ++j) {
                int p = i + j;
                if (ans[p] == '?') {
                    ans[p] = str2[j];
                    fixed[p] = 1;
                } else if (ans[p] != str2[j]) {
                    return "";
                }
            }
        }

        for (int p = 0; p < L; ++p) {
            if (ans[p] == '?') {
                ans[p] = 'a';
            }
        }

        for (int i = 0; i < n; ++i) {
            if (str1[i] != 'F') {
                continue;
            }

            bool equal = true;
            for (int j = 0; j < m; ++j) {
                if (ans[i + j] != str2[j]) {
                    equal = false;
                    break;
                }
            }
            if (!equal) {
                continue;
            }

            int pick = -1;
            for (int j = m - 1; j >= 0; --j) {
                int p = i + j;
                if (!fixed[p] && ans[p] == 'a') {
                    pick = p;
                    break;
                }
            }
            if (pick == -1) {
                return "";
            }
            ans[pick] = 'b';
        }

        for (int i = 0; i < n; ++i) {
            bool equal = true;
            for (int j = 0; j < m; ++j) {
                if (ans[i + j] != str2[j]) {
                    equal = false;
                    break;
                }
            }
            if (str1[i] == 'T' && !equal) {
                return "";
            }
            if (str1[i] == 'F' && equal) {
                return "";
            }
        }

        return ans;
    }
};

class Solution {
public:
    string generateString(string str1, string str2) {
        return Solver3474Greedy().solve(str1, str2);
    }
};