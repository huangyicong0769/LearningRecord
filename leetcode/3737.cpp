#include "lc.hpp"

class Solution {
public:
    int countMajoritySubarrays(vector<int>& nums, int target) {
        const int N = nums.size();
        int ans = 0;
        for (int i = 0; i < N; ++i) {
            int cnt = 0;
            for (int j = i; j < N; ++j) {
                cnt += (nums[j] == target);
                ans += (cnt > (j - i + 1) / 2);
            }
        }
        return ans;
    }
};

class Solution {
public:
    int countMajoritySubarrays(vector<int>& nums, int target) {
        const int N = nums.size();
        int ans = 0;
        for (int i = 0; i < N; i++)
            nums[i] = (i == 0 ? 0 : nums[i - 1]) + (nums[i] == target);
        for (int i = 0; i < N; ++i) {
            for (int j = i; j < N; ++j)
                ans += ((nums[j] - (i == 0 ? 0 : nums[i - 1])) > (j - i + 1) / 2);
        }
        return ans;
    }
};