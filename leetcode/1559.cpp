#include "lc.hpp"

class Solution {
    const int d[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    std::vector<std::vector<int>> visit;
    std::unique_ptr<std::vector<std::vector<char>>> grid;
    
    bool dfs(int x, int y, int px, int py){
        if (visit[x][y]) return true;
        visit[x][y] = 1;
        for (int i = 0; i < 4; i++){
            int nx = x + d[i][0], ny = y + d[i][1];
            if (nx < 0 || nx >= visit.size() || ny < 0 || ny >= visit[0].size() || (*grid)[nx][ny] != (*grid)[x][y] || (nx == px && ny == py)) continue;
            if (dfs(nx, ny, x, y)) return true;
        }
        return false;
    }

public:
    bool containsCycle(vector<vector<char>>& grid) {
        const int N = grid.size(), M = grid[0].size();
        this->grid = std::make_unique<std::vector<std::vector<char>>>(std::move(grid));
        visit.assign(N, std::vector<int>(M, 0));
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                if (visit[i][j] == 0 && dfs(i, j, -1, -1)) return true;
        return false;
    }
};