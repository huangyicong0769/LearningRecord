#include "lc.hpp"

class Solution {
public:
    bool canPartitionGrid(vector<vector<int>>& grid) {
        const int N = grid.size();
        const int M = grid[0].size();
        vector line(N, 0LL);
        vector col(M, 0LL);
        for (int i = 0; i < N; i++){
            for (int j = 0; j < M; j++){
                line[i] += grid[i][j];
                col[j] += grid[i][j];
            }
        }
        
        for (int i = 1; i < N; i++)
            line[i] += line[i - 1];
        for (int j = 1; j < M; j++)
            col[j] += col[j - 1];

        // auto p = [](const vector<int> v){
        //     for (const auto &a:v)
        //         cout << a << ", ";
        //     cout << endl;
        // };

        // p(line);
        // p(col);

        const auto & sum = line[N - 1];
        if (sum % 2)
            return false;
        for (int i = 0; i < N - 1; i++)
            if (line[i] == sum - line[i])
                return true;
            else if (line[i] > sum - line[i])
                break;
        for (int j = 0; j < M - 1; j++)
            if (col[j] == sum - col[j])
                return true;
            else if (col[j] > sum - col[j])
                break;
        return false;
    }
};