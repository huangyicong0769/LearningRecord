#include "lc.hpp"

class Solution {
    std::vector<vector<int>> cost, cap;
    std::vector<long long> dis;
    std::vector<bool> vis;
    int S = 0, T = 1, N1, N2;

    bool spfa(){
        std::ranges::fill(dis, LLONG_MAX);
        std::queue<int> q;
        q.push(S);
        dis[S] = 0;
        vis[S] = true;
        while (!q.empty()){
            int u = q.front();
            q.pop();
            for (int i = 0; i < N1 + N2 + 2; i++){
                if (cap[u][i] == 0 || dis[i] <= dis[u] + cost[u][i]) continue;
                dis[i] = dis[u] + cost[u][i];
                if (!vis[i]){
                    q.push(i);
                    vis[i] = true;
                }
            }
            vis[u] = false;
        }
        return dis[T] != LLONG_MAX;
    }

    std::pair<int, long long> dfs(int u, int flow){
        if (u == T) return {flow, 0LL};
        vis[u] = true;
        int div = 0;
        long long ex = 0LL;
        for (int i = 0; i < N1 + N2 + 2 && div < flow; i++){
            if (vis[i] || cap[u][i] == 0 || dis[i] != dis[u] + cost[u][i]) continue;
            auto [x, y] = dfs(i, std::min(flow - div, cap[u][i]));
            if (x){
                div += x;
                ex += x * cost[u][i] + y;
                cap[u][i] -= x;
                cap[i][u] += x;
            }
        }
        vis[u] = false;
        return {div, ex};
    }

public:
    long long minimumTotalDistance(vector<int>& robot, vector<vector<int>>& factory) {
        N1 = robot.size(), N2 = factory.size();
        cost.assign(N1 + N2 + 2, std::vector<int>(N1 + N2 + 2, 0));
        cap.assign(N1 + N2 + 2, std::vector<int>(N1 + N2 + 2, 0));
        dis.assign(N1 + N2 + 2, LLONG_MAX);
        vis.assign(N1 + N2 + 2, false);

        for (int i = 0; i < N1; i++)
            cap[S][i + 2] = 1;
        for (int i = 0; i < N2; i++)
            cap[i + 2 + N1][T] = factory[i][1];
        for (int i = 0; i < N1; i++)
            for (int j = 0; j < N2; j++){
                cap[i + 2][j + 2 + N1] = 1;
                cost[i + 2][j + 2 + N1] = abs(robot[i] - factory[j][0]);
                cost[j + 2 + N1][i + 2] = -cost[i + 2][j + 2 + N1];
            }
        
        long long ans = 0;
        while (spfa()){
            while (true){
                auto [x, y] = dfs(S, INT_MAX);
                if (x == 0) break;
                ans += y;
            }
        }
        return ans;
    }
};

