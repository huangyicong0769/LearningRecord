#include "lc.hpp"

class Solution {
public:
    bool findRotation(vector<vector<int>>& mat, vector<vector<int>>& target) {
        auto rotate = [](vector<vector<int>> &x){
            const int N = x.size();
            const int M = x[0].size();
            auto y = x;
            for (int i = 0; i < N; i++)
                for (int j = 0; j < M; j++)
                    x[j][N - i - 1] = y[i][j];
        };
        auto equal = [](const vector<vector<int>> &x, const vector<vector<int>> &y) -> bool {
            const int N = x.size();
            const int M = x[0].size();
            for (int i = 0; i < N; i++)
                for (int j = 0; j < M; j++)
                    if (x[i][j] != y[i][j])
                        return false;
            return true;
        };

        for (int i = 0; i < 4; i++){
            if (equal(mat, target))
                return true;
            rotate(mat);
        }
        return false;
    }
};