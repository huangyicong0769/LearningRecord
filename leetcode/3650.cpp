#include "lc.hpp"

class Solution {
public:
    int minCost(int n, vector<vector<int>>& edges) {
        // Build one adjacency list to keep cache-friendly access and smaller constants.
        vector<vector<pair<int, int>>> g(n);
        g.reserve(n);
        for (const auto &e : edges) {
            int u = e[0], v = e[1], w = e[2];
            g[u].push_back({v, w});       // forward edge cost w
            g[v].push_back({u, 2 * w});   // reverse edge cost 2w
        }

        // Standard Dijkstra with (cost, node) min-heap.
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        vector<int> dist(n, INT_MAX);
        dist[0] = 0;
        pq.push({0, 0});

        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            if (d != dist[u]) continue; // stale state
            if (u == n - 1) return d;   // early exit when we pop target

            for (const auto &[v, w] : g[u]) {
                int nd = d + w;
                if (nd < dist[v]) {
                    dist[v] = nd;
                    pq.push({nd, v});
                }
            }
        }
        return -1;
    }
};