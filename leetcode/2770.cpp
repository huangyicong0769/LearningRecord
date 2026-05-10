#include "lc.hpp"

class Solution {
public:
    int maximumJumps(vector<int>& nums, int target) {
        const int N = nums.size();
        std::vector<int> f(N,  -1);
        f[0] = 0;
        for (int i = 1; i < N; i++){
            for (int j = 0; j < i; j++){
                if (f[j] != -1 && abs(nums[i] - nums[j]) <= target)
                    f[i] = max(f[i], f[j] + 1);
            }
        }
        return f[N - 1];
    }
};