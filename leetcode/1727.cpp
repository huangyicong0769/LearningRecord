#include "lc.hpp"

class Solution {
public:
    int largestSubmatrix(vector<vector<int>>& matrix) {
        const int N = matrix.size();
        const int M = matrix[0].size();
        for (int i = 1; i < N; i++)
            for (int j = 0; j < M; j++){
                if (matrix[i][j])
                    matrix[i][j] += matrix[i - 1][j];
            }
        int ans = 0;
        for (int i = 0; i < N; i++){
            sort(matrix[i].begin(), matrix[i].end(), std::greater<int>());
            for (int j = 0; j < M && matrix[i][j]; j++)
                ans = max(ans, (j + 1) * matrix[i][j]);
        }
        return ans;
    }
};