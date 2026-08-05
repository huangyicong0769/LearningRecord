#include "lc.hpp"

class Solution {
public:
    vector<int> findMissingElements(vector<int>& nums) {
        vector<char> frep(101, 0);
        int max = 0, min = 101;
        for (int i : nums) {
            frep[i] = 1;
            max = std::max(max, i);
            min = std::min(min, i);
        }
        vector<int> ans;
        for (int i = min; i <= max; i++) {
            if (!frep[i])
                ans.push_back(i);
        }
        return ans;
    }
};