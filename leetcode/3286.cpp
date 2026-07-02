#include "lc.hpp"

class Solution {
    static constexpr std::pair<int, int> directions[4] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
public:
    bool findSafeWalk(vector<vector<int>>& grid, int health) {
        const int M = grid.size(), N = grid[0].size();
        std::vector<std::vector<int>> dp(M, std::vector<int>(N, -1));
        std::priority_queue<std::tuple<int, int, int>> pq; // (health, x, y)
        int h0 = health - grid[0][0];
        if (h0 <= 0) return false;
        pq.emplace(h0, 0, 0);
        while (!pq.empty()) {
            auto [h, x, y] = pq.top(); pq.pop();
            if (x == M - 1 && y == N - 1) return true;
            if (dp[x][y] >= h) continue;
            dp[x][y] = h;
            for (auto [dx, dy] : directions) {
                int nx = x + dx, ny = y + dy;
                if (nx >= 0 && nx < M && ny >= 0 && ny < N) {
                    int nh = h - grid[nx][ny];
                    if (nh > 0) {
                        pq.emplace(nh, nx, ny);
                    }
                }
            }
        }
        return false;
    }
};

class Solution {
    static constexpr std::pair<int, int> directions[4] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
public:
    bool findSafeWalk(vector<vector<int>>& grid, int health) {
        const int M = grid.size(), N = grid[0].size();
        std::vector<std::vector<int>> dp(M, std::vector<int>(N, -1));
        std::deque<std::tuple<int, int, int>> pq; // (health, x, y)
        int h0 = health - grid[0][0];
        if (h0 <= 0) return false;
        pq.emplace_front(h0, 0, 0);
        while (!pq.empty()) {
            auto [h, x, y] = pq.front(); pq.pop_front();
            if (x == M - 1 && y == N - 1) return true;
            if (dp[x][y] >= h) continue;
            dp[x][y] = h;
            for (auto [dx, dy] : directions) {
                int nx = x + dx, ny = y + dy;
                if (nx >= 0 && nx < M && ny >= 0 && ny < N) {
                    int nh = h - grid[nx][ny];
                    if (nh > 0) {
                        if (grid[nx][ny])
                            pq.emplace_back(nh, nx, ny);
                        else
                            pq.emplace_front(nh, nx, ny);
                    }
                }
            }
        }
        return false;
    }
};