#include "lc.hpp"

class Solution {
public:
    int maxSideLength(vector<vector<int>>& mat, int threshold) {
        const int N = mat.size(), M = mat[0].size();
        vector<vector<int>> s(N + 1, vector<int>(M + 1, 0));
        for (int i = 1; i <= N; i++)
            for (int j = 1; j <= M; j++)
                s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1] + mat[i - 1][j - 1];
        
        auto check = [&](int k) -> bool {
            for (int i = k; i <= N; i++)
                for (int j = k; j <= M; j++)
                    if (s[i][j] - s[i - k][j] - s[i][j - k] + s[i - k][j - k] <= threshold)
                        return true;
            return false;
        };
        
        int ans = 0;
        for (int l = 1, r = min(N, M); l <= r;){
            int mid = (l + r) / 2;
            if (check(mid)){
                ans = mid;
                l = mid + 1;
            }else r = mid - 1;
        }
        return ans;
    }
};