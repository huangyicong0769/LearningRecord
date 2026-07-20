#include "lc.hpp"

class Solution {
public:
    int findGCD(vector<int>& nums) {
        return std::gcd(std::ranges::min(nums), std::ranges::max(nums));      
    }
};