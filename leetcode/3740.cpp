// Also for 3741
#include "lc.hpp"

class Solution {
public:
    int minimumDistance(vector<int>& nums) {
        std::unordered_map<int, vector<int>> pos;
        for (int i = 0; i < nums.size(); i++)
            pos[nums[i]].push_back(i);
        int ans = INT_MAX;
        for (const auto &[_, v]:pos){
            for (int i = 1; i < v.size() - 1; i++)
                ans = min(ans, v[i + 1] - v[i - 1]);
        }
        return ans == INT_MAX ? -1 : 2 * ans;
    }
};