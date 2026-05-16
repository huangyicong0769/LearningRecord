#include "lc.hpp"

class Solution {
public:
    int findMin(vector<int>& nums) {
        int ans = 5001;
        int l = 0, r = nums.size() - 1;
        while (l <= r) {
            int m = l + (r - l) / 2;
            if (nums[l] < nums[m] && nums[m] < nums[r]) {
                ans = min(ans, nums[l]);
                break;
            }
            if (nums[l] > nums[m]){
                ans = min(ans, nums[m]);
                r = m - 1;
            } else {
                ans = min(ans, nums[l]);
                l = m + 1;
            }
        }
        return ans;
    }
};