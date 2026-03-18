#include "lc.hpp"

class Solution {
public:
    int countSubmatrices(vector<vector<int>>& grid, int k) {
        const int N = grid.size();
        const int M = grid[0].size();
        vector s(N + 1, vector<int>(M + 1));
        
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                s[i + 1][j + 1] = s[i][j + 1] + s[i + 1][j] - s[i][j] + grid[i][j];
        
        int ans = 0, m = M;
        for (int i  = 0; i < N; i++){
            for (int j = 0; j < m; j++){
                if (s[i + 1][j + 1] > k){
                    m = j;
                    break;
                }
                ans++;
            }
        }
        return ans;
    }
};