#include "lc.hpp"

class Solution {
public:
    int maximumLength(vector<int>& nums) {
        std::unordered_map<int, std::vector<int>> h;
        int ones = 0;
        for (int x: nums){
            if (x == 1){
                ones++;
                continue;
            }
            int k = 0;
            if (h[x].size() <= k) h[x].resize(k + 1, 0);
            h[x][k]++;
            for (int y = sqrt(x); x > 1 && y * y == x; y = sqrt(x)){
                x = y;
                k += 1;
                if (h[x].size() <= k) h[x].resize(k + 1, 0);
                h[x][k]++;
            }
        }
        int ans = ones > 0 ? ones - (ones % 2 == 0) : 1;
        for (const auto& [x, v]: h){
            int k = v.size();
            int cnt = 0;
            for (int i = 0; i < k; i++)
                if (v[i] < 2){
                    if (v[i] == 1)
                        cnt++;
                    break;
                } else {
                    cnt++;
                }
            if (cnt > 0)
                ans = std::max(ans, 2 * cnt - 1);
        }
        return ans;
    }
};