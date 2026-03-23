#include "lc.hpp"

class Solution {
public:
    int maxProductPath(vector<vector<int>>& grid) {
        const int N = grid.size();
        const int M = grid[0].size();
        const int MOD = static_cast<int>(1e9 + 7);

        vector<vector<array<long long, 3>>> f(
            N,
            vector<array<long long, 3>>(M, array<long long, 3>{-1LL, 0LL, -1LL})
        );

        auto relax = [&](array<long long, 3>& cur, const array<long long, 3>& pre, int num) {
            if (pre[0] != -1LL) {
                const long long v = pre[0] * 1LL * num;
                if (v > 0) cur[0] = max(cur[0], v);
                else if (v == 0) cur[1] = 1LL;
                else cur[2] = max(cur[2], -v);
            }

            if (pre[1]) {
                cur[1] = 1LL;
            }

            if (pre[2] != -1LL) {
                const long long v = (-pre[2]) * 1LL * num;
                if (v > 0) cur[0] = max(cur[0], v);
                else if (v == 0) cur[1] = 1LL;
                else cur[2] = max(cur[2], -v);
            }
        };

        if (grid[0][0] > 0) f[0][0][0] = grid[0][0];
        else if (grid[0][0] == 0) f[0][0][1] = 1LL;
        else f[0][0][2] = -1LL * grid[0][0];

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (i == 0 && j == 0) continue;
                if (i > 0) relax(f[i][j], f[i - 1][j], grid[i][j]);
                if (j > 0) relax(f[i][j], f[i][j - 1], grid[i][j]);
            }
        }

        if (f[N - 1][M - 1][0] != -1LL) {
            return static_cast<int>(f[N - 1][M - 1][0] % MOD);
        }
        if (f[N - 1][M - 1][1]) {
            return 0;
        }
        return -1;
    }
};