#include "lc.hpp"

class Solution {
    std::vector<int> pre;
    int f[50001] = {0};
    bool vis[50001] = {false};

    int dfs(int i) {
        if (vis[i]) return f[i];
        vis[i] = true;
        if (i == pre.size())
            return f[i] = 0;
        f[i] = INT_MIN;
        int sum = 0;
        for (int x = 1; x <= 3 && i + x <= pre.size(); x++) {
            int nx = i + x;
            sum += pre[nx - 1];
            f[i] = std::max(f[i], sum - dfs(nx));
        }
        return f[i];
    }

public:
    string stoneGameIII(vector<int>& stoneValue) {
        const int N = stoneValue.size();
        pre = stoneValue;
        // for (int i = 1; i < N; i++)
        //     pre[i] += pre[i - 1];
        return dfs(0) > 0 ? "Alice" : dfs(0) < 0 ? "Bob" : "Tie";
    }
};