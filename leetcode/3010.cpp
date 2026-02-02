#include "lc.hpp"

class Solution {
public:
    int minimumCost(vector<int>& nums) {
        std::sort(std::next(nums.begin()), nums.end());
        return std::accumulate(nums.begin(), std::next(nums.begin(), 3), 0);
    }
};