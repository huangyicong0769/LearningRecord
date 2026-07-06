#include "lc.hpp"

class Solution {
public:
    int minScore(int n, vector<vector<int>>& roads) {
        std::vector<std::vector<std::pair<int, int>>> edges(n + 1);
        for (const auto& road : roads) {
            edges[road[0]].push_back({road[1], road[2]});
            edges[road[1]].push_back({road[0], road[2]});
        }
        vector<char> vis(n + 1, false);
        queue<int> q;
        q.push(1);
        vis[1] = true;
        int ans = INT_MAX;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (auto [v, w] : edges[u]) {
                ans = min(ans, w);
                if (!vis[v]) {
                    vis[v] = true;
                    q.push(v);
                }
            }
        }
        return ans;
    }
};