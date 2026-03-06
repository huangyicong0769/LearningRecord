#include "lc.hpp"

class Solution {
public:
    int minSwaps(vector<vector<int>>& grid) {
        const size_t N = grid.size();
        vector<int> a;
        a.reserve(N);
        for (int i = 0; i < N; i++){
            int cnt = 0;
            for (int j = N - 1; j >= 0 && grid[i][j] == 0; j--)
                cnt++;
            a.push_back(cnt);
        }
        // sort(a.begin(), a.end(), [&](const auto &a, const auto &b) -> bool {
        //     return a.first > b.first || a.first == b.first && a.second < b.second;
        // });

        int ans = 0;
        for (int i = 0; i < N; i++){
            if (a[i] >= N - i - 1) 
                continue;
            int k = i + 1;
            while (k < N && a[k] < N - i - 1) k++;
            if (k == N)
                return -1;
            for (int j = k; j > i; j--){
                swap(a[j], a[j - 1]);
                ans++;
            }
        }
        return ans;
    }
};