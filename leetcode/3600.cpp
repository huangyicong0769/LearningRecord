#include "lc.hpp"

using T3i = tuple<int, int, int>;

class Solution {
    vector<int> fa;

    int getfa(int x){
        if (fa[x] == x) return x;
        fa[x] = getfa(fa[x]);
        return fa[x];
    }

public:
    int maxStability(int n, vector<vector<int>>& edges, int k) {
        fa.assign(n, 0);
        vector<T3i> e;

        auto min_cmp = [](const T3i &a, const T3i &b){
            return get<2>(a) > get<2>(b);
        };
        priority_queue<T3i, vector<T3i>, decltype(min_cmp)> min_heap(min_cmp);

        auto max_cmp = [](const T3i &a, const T3i &b){
            return get<2>(a) < get<2>(b);
        };
        priority_queue<T3i, vector<T3i>, decltype(max_cmp)> max_heap(max_cmp);

        for (int i = 0; i < n; i++)
            fa[i] = i;
        
        int ans = INT_MAX;
        int sum_edge = 0;
        for (const auto &edge:edges){
            if (edge[3]){
                if (getfa(edge[0]) == getfa(edge[1]))
                    return -1;
                ans = min(ans, edge[2]);
                sum_edge++;
                fa[getfa(edge[0])] = getfa(edge[1]);
            }else
                max_heap.push({edge[0], edge[1], edge[2]});
        }

        while (sum_edge < n - 1){
            if (max_heap.empty())
                return -1;
            auto [u, v, s] = max_heap.top();
            max_heap.pop();
            if (getfa(u) == getfa(v))
                continue;
            sum_edge++;
            fa[getfa(u)] = getfa(v);
            min_heap.push({u, v, s});
        }
        
        for (int i = 0; i < k && min_heap.size(); i++){
            auto [u, v, s] = min_heap.top();
            min_heap.pop();
            ans = min(ans, s*2);
        }
        if (!min_heap.empty()){
            ans = min(ans, get<2>(min_heap.top()));
        }
        return ans;
    }
};

class SolutionOptimized {
    struct DSU {
        vector<int> fa;
        vector<int> sz;

        explicit DSU(int n) : fa(n), sz(n, 1) {
            iota(fa.begin(), fa.end(), 0);
        }

        int find(int x) {
            while (fa[x] != x) {
                fa[x] = fa[fa[x]];
                x = fa[x];
            }
            return x;
        }

        bool unite(int a, int b) {
            a = find(a);
            b = find(b);
            if (a == b) return false;
            if (sz[a] < sz[b]) swap(a, b);
            fa[b] = a;
            sz[a] += sz[b];
            return true;
        }
    };

    struct Edge {
        int u;
        int v;
        int w;
    };

public:
    int maxStability(int n, vector<vector<int>>& edges, int k) {
        DSU dsu(n);
        vector<Edge> optional;
        optional.reserve(edges.size());

        int ans = INT_MAX;
        int used = 0;

        for (const auto &edge : edges) {
            const int u = edge[0];
            const int v = edge[1];
            const int w = edge[2];
            const int forced = edge[3];

            if (forced) {
                if (!dsu.unite(u, v)) return -1;
                ans = min(ans, w);
                ++used;
            } else {
                optional.push_back({u, v, w});
            }
        }

        sort(optional.begin(), optional.end(), [](const Edge &a, const Edge &b) {
            return a.w > b.w;
        });

        vector<int> chosen;
        chosen.reserve(optional.size());

        for (const auto &e : optional) {
            if (used == n - 1) break;
            if (!dsu.unite(e.u, e.v)) continue;
            ++used;
            chosen.push_back(e.w);
        }

        if (used < n - 1) return -1;

        const int m = static_cast<int>(chosen.size());
        const int t = min(k, m);

        int idx = 0;
        for (int w : std::ranges::reverse_view(chosen)) {
            if (idx < t) {
                ans = min(ans, w * 2);
            } else {
                ans = min(ans, w);
                break;
            }
            ++idx;
        }

        return ans;
    }
};