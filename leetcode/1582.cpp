#include "lc.hpp"

class Solution {
public:
    int numSpecial(vector<vector<int>>& mat) {
        const size_t N = mat.size();
        const size_t M = mat[0].size();
        vector<int> row(N), col(M);
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++){
                row[i] += mat[i][j];
                col[j] += mat[i][j];
            }
        int ans = 0;
        for (int i = 0; i < N; i++)
            if (row[i] == 1)
                for (int j = 0; j < M; j++)
                    if (mat[i][j] && col[j] == 1)
                        ans++;
        return ans;
    }
};