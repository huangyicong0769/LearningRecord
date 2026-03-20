#include "lc.hpp"

class Solution {
public:
    vector<vector<int>> minAbsDiff(vector<vector<int>>& grid, int k) {
        const int N = grid.size();
        const int M = grid[0].size();
        vector ans (N - k + 1, vector<int>(M - k + 1, 0));
        vector tmp (k * k, 0);
        for (int i = 0; i < N - k + 1; i++)
            for (int j = 0; j < M - k + 1; j++){
                tmp.clear();
                for (int k1 = i; k1 < i + k; k1++)
                    for (int k2 = j; k2 < j + k; k2++)
                        tmp.push_back(grid[k1][k2]);
                sort(tmp.begin(), tmp.end());
                ans[i][j] = 0;
                for (int t = 1; t < k * k; t++){
                    if (tmp[t - 1] == tmp[t])
                        continue;
                    ans[i][j] = ans[i][j] ? min(ans[i][j], tmp[t] - tmp[t - 1]) : tmp[t] - tmp[t - 1];
                }
            }
        return ans;
    }
};