#include "lc.hpp"

class Solution {
public:
    long long gcdSum(vector<int>& nums) {
        int mx = nums[0];
        for (int i = 1; i < nums.size(); ++i) {
            mx = max(mx, nums[i]);
            nums[i] = std::gcd(mx, nums[i]);
        }
        std::sort(nums.begin(), nums.end());
        long long ans = 0;
        for (int i = 0, j = nums.size() - 1; i < j; i++, j--)
            ans += std::gcd(nums[i], nums[j]);
        return ans;
    }
};