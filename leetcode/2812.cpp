#include "lc.hpp"

class Solution {
public:
    int maximumSafenessFactor(vector<vector<int>>& grid) {
        const int N = grid.size();
        std::vector dist(N, std::vector<int>(N, -1));
        std::queue<std::pair<int, int>> q;
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                if (grid[i][j] == 1){
                    dist[i][j] = 0;
                    q.push({i, j});
                }
        while (!q.empty()){
            auto [i, j] = q.front();
            q.pop();
            for (int k = 0; k < 4; k++){
                int ni = i + "2101"[k] - '1';
                int nj = j + "1210"[k] - '1';
                if (ni < 0 || ni >= N || nj < 0 || nj >= N || dist[ni][nj] != -1)
                    continue;
                dist[ni][nj] = dist[i][j] + 1;
                q.push({ni, nj});
            }
        }
        std::vector f(N, std::vector<int>(N, -1));
        std::priority_queue<std::tuple<int, int, int>> pq;

        f[0][0] = dist[0][0];
        pq.push({f[0][0], 0, 0});

        while (!pq.empty()) {
            auto [safe, i, j] = pq.top();
            pq.pop();

            if (safe < f[i][j])
                continue;

            if (i == N - 1 && j == N - 1)
                return safe;

            for (int k = 0; k < 4; k++) {
                int ni = i + "2101"[k] - '1';
                int nj = j + "1210"[k] - '1';

                if (ni < 0 || ni >= N || nj < 0 || nj >= N)
                    continue;

                int nsafe = std::min(safe, dist[ni][nj]);

                if (nsafe > f[ni][nj]) {
                    f[ni][nj] = nsafe;
                    pq.push({nsafe, ni, nj});
                }
            }
        }

        return f[N - 1][N - 1];
    }
};