#include "lc.hpp"

class Solution {
public:
    vector<vector<int>> shiftGrid(vector<vector<int>>& grid, int k) {
        const int M = grid.size(), N = grid[0].size();
        vector<vector<int>> ans(M, vector<int>(N));
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                int newIndex = (i * N + j + k) % (M * N);
                ans[newIndex / N][newIndex % N] = grid[i][j];
            }
        }
        return ans;
    }
};