#include "lc.hpp"

class Solution {
    const int d[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    const int b[6][2] = {{0, 1}, {2, 3}, {1, 2}, {0, 2}, {1, 3}, {0, 3}};
public:
    bool hasValidPath(vector<vector<int>>& grid) {
        const int m = grid.size(), n = grid[0].size();

        auto legal = [&](int x, int y) {
            return x >= 0 && x < m && y >= 0 && y < n;
        };

        auto canBack = [&](int x, int y, int backDir) {
            const int t = grid[x][y] - 1;
            return b[t][0] == backDir || b[t][1] == backDir;
        };

        queue<pair<int, int>> q;
        vector<vector<int>> vis(m, vector<int>(n, 0));
        q.push({0, 0});
        vis[0][0] = 1;

        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();
            if (x == m - 1 && y == n - 1) return true;

            const int t = grid[x][y] - 1;
            for (int k = 0; k < 2; ++k) {
                const int dir = b[t][k];
                const int nx = x + d[dir][0];
                const int ny = y + d[dir][1];
                const int backDir = dir ^ 1;

                if (!legal(nx, ny) || vis[nx][ny]) continue;
                if (!canBack(nx, ny, backDir)) continue;

                vis[nx][ny] = 1;
                q.push({nx, ny});
            }
        }
        return false;
    }
};