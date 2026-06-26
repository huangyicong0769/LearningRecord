#include "lc.hpp"

class Solution {
public:
    long long countMajoritySubarrays(vector<int>& nums, int target) {
        const int N = nums.size();
        long long ans = 0, pre = 0;
        int sum = N;
        std::vector<int> cnt(2 * N + 1);
        cnt[N] = 1;
        for (int i = 0; i < N; i++){
            if (nums[i] == target)
                pre += cnt[sum++];
            else
                pre -= cnt[--sum];
            cnt[sum]++;
            ans += pre;
        }
        return ans;
    }
};