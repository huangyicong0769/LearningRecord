#include "lc.hpp"

class Solution {
    static constexpr int MOD = 1'000'000'007;

public:
    int subsequencePairCount(vector<int>& nums) {
        const int m = std::ranges::max(nums) + 1;

        vector<int> f(m * m), g(m * m);
        auto id = [m](int x, int y) {
            return x * m + y;
        };
        auto add = [](int& x, int y) {
            x += y;
            if (x >= MOD) {
                x -= MOD;
            }
        };

        f[id(0, 0)] = 1;
        for (int v : nums) {
            ranges::fill(g, 0);
            for (int x = 0; x < m; ++x)
                for (int y = 0; y < m; ++y) {
                    int c = f[id(x, y)];
                    if (c == 0) {
                        continue;
                    }
                    int a = std::gcd(x, v);
                    int b = std::gcd(y, v);
                    add(g[id(a, y)], c);
                    add(g[id(x, b)], c);
                    add(g[id(x, y)], c);
                }
            f.swap(g);
        }
        int ans = 0;
        for (int d = 1; d < m; ++d)
            add(ans, f[id(d, d)]);
        return ans;
    }
};