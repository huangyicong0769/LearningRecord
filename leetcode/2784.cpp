#include "lc.hpp"

class Solution {
public:
    bool isGood(vector<int>& nums) {
        std::vector<int> count(201);
        int m = -1;
        for (int x : nums){
            count[x]++;
            m = max(m, x);
        }
        if (m + 1 != nums.size()) return false;
        for (int i = 1; i < m; i++)
            if (count[i] != 1)
                return false;
        return count[m] == 2;
    }
};