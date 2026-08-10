#include "lc.hpp"

class Solution {
    std::vector<std::vector<int>> g;
    std::vector<char> buggy;

    void dfs1(int u) {
        buggy[u] = 1;
        for (int v : g[u]) {
            if (!buggy[v])
                dfs1(v);
        }
    }

public:
    vector<int> remainingMethods(int n, int k, vector<vector<int>>& invocations) {
        g.assign(n, {});
        buggy.assign(n, 0);
        for (auto& e : invocations)
            g[e[0]].push_back(e[1]);
        dfs1(k);
        for (int i = 0; i < n; i++) {
            if (buggy[i])
                continue;
            bool ok = true;
            for (int v : g[i])
                if (buggy[v]) {
                    ok = false;
                    break;
                }
            if (!ok)
                return std::ranges::iota_view(0, n) | std::ranges::to<std::vector>();
        }
        std::vector<int> ans;
        for (int i = 0; i < n; i++)
            if (!buggy[i])
                ans.push_back(i);
        return ans;
    }
};