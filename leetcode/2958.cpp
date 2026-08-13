#include "lc.hpp"

class Solution {
public:
    int maxSubarrayLength(vector<int>& nums, int k) {
        std::unordered_map<int, int> f;
        const int N = nums.size();
        int ans = 0;
        for (int l = 0, r = 0; r < N; r++){
            f[nums[r]]++;
            while (l < r && f[nums[r]] > k){
                f[nums[l]]--;
                l++;
            }
            ans = std::max(ans, r - l + 1);
        }
        return ans;
    }
};