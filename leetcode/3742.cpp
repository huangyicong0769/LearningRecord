#include "lc.hpp"

class Solution {
public:
    int maxPathScore(vector<vector<int>>& grid, int K) {
        const int N = grid.size(), M = grid[0].size();
        std::vector<std::vector<int>> x(M, std::vector<int>(K + 1, -1)), y(M, std::vector<int>(K + 1, -1));

        auto update = [&](int&x, int v){
            if (x == -1) x = v;
            else x = std::max(x, v);
        };

        x[0][grid[0][0] ? 1 : 0] = grid[0][0];
        for (int j = 1; j < M; ++j) {
            for (int k = 0; k <= K; ++k) {
                const int &v = grid[0][j];
                const int nk = k - (v ? 1 : 0);
                if (nk < 0 || x[j - 1][nk] == -1) continue;
                update(x[j][k], x[j - 1][nk] + v);
            }
        }
        for (int i = 1; i < N; ++i) {
            std::fill(y.begin(), y.end(), std::vector<int>(K + 1, -1));
            for (int k = 0; k <= K; ++k) {
                const int &v = grid[i][0];
                const int nk = k - (v ? 1 : 0);
                if (nk < 0 || x[0][nk] == -1) continue;
                update(y[0][k], x[0][nk] + v);
            }
            for (int j = 1; j < M; ++j) {
                for (int k = 0; k <= K; ++k) {
                    const int &v = grid[i][j];
                    const int nk = k - (v ? 1 : 0);
                    if (nk < 0) continue;
                    if (x[j][nk] != -1) update(y[j][k], x[j][nk] + v);
                    if (y[j - 1][nk] != -1) update(y[j][k], y[j - 1][nk] + v);
                }
            }
            std::swap(x, y);
        }
        return std::ranges::max(x[M - 1]);
    }
};