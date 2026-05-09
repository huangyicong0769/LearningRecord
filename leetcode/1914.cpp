#include "lc.hpp"

class Solution {
public:
    vector<vector<int>> rotateGrid(vector<vector<int>>& grid, int k) {
        const int M = grid.size(), N = grid[0].size();
        vector<vector<int>> ans(M, vector<int>(N));

        auto idx = [&](int i, int l)->pair<int, int> {
            int m = M - 2 * l - 1, n = N - 2 * l - 1;
            if (i < m) return {i + l, l};
            i -= m;
            if (i < n) return {M - l - 1, i + l};
            i -= n;
            if (i < m) return {M - l - 1 - i, N - l - 1};
            i -= m;
            return {l, N - l - 1 - i};
        };

        for (int l = 0; l < min(M, N) / 2; l++){
            for (int i = 0; i < 2 * (M + N - 4 * l) - 4; i++){
                auto [x, y] = idx(i, l);
                auto [x2, y2] = idx((i + k) % (2 * (M + N - 4 * l) - 4), l);
                ans[x2][y2] = grid[x][y];
            }
        }
        return ans;
    }
};