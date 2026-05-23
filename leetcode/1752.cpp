#include "lc.hpp"

class Solution {
public:
    bool check(vector<int>& nums) {
        int cnt = 0;
        nums.push_back(*nums.begin());
        for (int i = 1; i < nums.size(); ++i) {
            if (nums[i] < nums[i - 1]) {
                if (++cnt > 1) return false;
            }
        }
        return true;
    }
};