#include "lc.hpp"

class Solution {
public:
    int missingInteger(vector<int>& nums) {
        std::vector<char> exists(100, 0);
        for (int x : nums)
            exists[x] = 1;

        int sum = nums[0];
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] != nums[i - 1] + 1)
                break;
            sum += nums[i];
        }

        while (sum < exists.size() && exists[sum])
            sum++;

        return sum;
    }
};