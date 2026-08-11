#include "lc.hpp"

class Solution {
    std::vector<int> pre;
    int f[101][101] = {0};
    bool vis[101][101] = {false};

    int dfs(int i, int M) {
        if (vis[i][M]) return f[i][M];
        vis[i][M] = true;
        int remain = pre.back() - (i > 0 ? pre[i - 1] : 0);
        for (int x = 1; x <= 2 * M && i + x <= pre.size(); x++) {
            int nx = i + x, nm = std::max(M, x);
            f[i][M] = std::max(f[i][M], remain - dfs(nx, nm));
        }
        return f[i][M];
    }

public:
    int stoneGameII(vector<int>& piles) {
        const int N = piles.size();
        pre = piles;
        for (int i = 1; i < N; i++)
            pre[i] += pre[i - 1];
        return dfs(0, 1);
    }
};