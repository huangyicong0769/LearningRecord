#include "lc.hpp"

class Solution {
    std::vector<vector<int>> g;
    std::vector<int> f;

    void dfs(int x){
        int t = 0;
        for (const int &y:g[x]){
            if (f[y] == 0){
                dfs(y);
            }
            t = max(t, f[y]);
        }
        f[x] = t + 1;
    }

public:
    int maxJumps(vector<int>& arr, int d) {
        const int N = arr.size();
        g.assign(N, std::vector<int>());
        for (int i = 0; i < N; i++){
            for (int x = 1; x <= d; x++){
                if (i - x < 0 || arr[i - x] >= arr[i])
                    break;
                g[i].push_back(i - x);
            }
            for (int x = 1; x <= d; x++){
                if (i + x >= N || arr[i + x] >= arr[i])
                    break;
                g[i].push_back(i + x);
            }
        }
        f.assign(N, 0);
        int ans = 0;
        for (int i = 0; i < N; i++){
            if (f[i] == 0)
                dfs(i);
            ans = max(ans, f[i]);
        }
        return ans;
    }
};