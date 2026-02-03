#include "lc.hpp"

class Solution {
public:
    bool isTrionic(vector<int>& nums) {
        int states = nums[0] < nums[1];
        if (!states)
            return false;
        int times = 0;
        for (int i = 1; i < nums.size(); i++){
            if (nums[i - 1] == nums[i])
                return false;
            if (states != nums[i - 1] < nums[i]){
                if (++times > 2)
                    return false; 
                states ^= 1;
            }
        }
        return times == 2;
    }
};