#include "lc.hpp"

class Solution {
public:
    long long maxTotalValue(vector<int>& nums, int k) {
        return 1LL * k * (std::ranges::max(nums) - std::ranges::min(nums));
    }
};