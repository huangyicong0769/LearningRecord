#include "lc.hpp"

class Solution {
public:
    vector<int> maxActiveSectionsAfterTrade(string s, vector<vector<int>>& queries) {
        const int N = s.size();

        std::vector<int> v, left, right, belong(N);
        int cnt = 1, start = 0;

        for (int i = 1; i < N; i++) {
            if (s[i] == s[i - 1]) {
                ++cnt;
            } else {
                int id = v.size();
                v.push_back(cnt);
                left.push_back(start);
                right.push_back(i - 1);

                for (int j = start; j < i; j++) {
                    belong[j] = id;
                }

                cnt = 1;
                start = i;
            }
        }

        int id = v.size();
        v.push_back(cnt);
        left.push_back(start);
        right.push_back(N - 1);

        for (int i = start; i < N; i++) {
            belong[i] = id;
        }

        const int M = v.size();
        const int base = std::count(s.begin(), s.end(), '1');

        std::vector<int> f(M, 0);
        int sign = s[0] - '0';

        for (int i = 0; i < M; i++) {
            if (sign && i >= 1 && i + 1 < M) {
                f[i] = v[i - 1] + v[i + 1];
            }
            sign ^= 1;
        }

        std::vector<int> lg(M + 1, 0);
        for (int i = 2; i <= M; i++) {
            lg[i] = lg[i >> 1] + 1;
        }

        const int K = lg[M];
        std::vector<int> st((K + 1) * M, 0);

        for (int i = 0; i < M; i++) {
            st[i] = f[i];
        }

        for (int k = 1; k <= K; k++) {
            const int len = 1 << k;
            const int half = len >> 1;
            const int cur = k * M;
            const int pre = (k - 1) * M;

            for (int i = 0; i + len <= M; i++) {
                st[cur + i] = std::max(
                    st[pre + i],
                    st[pre + i + half]
                );
            }
        }

        auto query = [&](int l, int r) {
            if (l > r) {
                return 0;
            }

            const int k = lg[r - l + 1];
            const int offset = k * M;

            return std::max(
                st[offset + l],
                st[offset + r - (1 << k) + 1]
            );
        };

        std::vector<int> ans;
        ans.reserve(queries.size());

        for (const auto& q : queries) {
            int l = q[0], r = q[1];
            int a = belong[l], b = belong[r];
            int mx = 0;

            auto check = [&](int i) {
                if (i <= a || i >= b || s[left[i]] == '0') {
                    return;
                }
                int x = std::min(right[i - 1], r) - std::max(left[i - 1], l) + 1;
                int y = std::min(right[i + 1], r) - std::max(left[i + 1], l) + 1;
                if (x > 0 && y > 0) {
                    mx = std::max(mx, x + y);
                }
            };
            check(a + 1);
            check(b - 1);
            mx = std::max(mx, query(a + 2, b - 2));

            ans.push_back(base + mx);
        }

        return ans;
    }
};