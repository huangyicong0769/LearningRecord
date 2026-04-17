#include "lc.hpp"

class Solution {
public:
    int minMirrorPairDistance(vector<int>& nums) {
        auto reverse = [](int x) -> int {
            int y = 0;
            while(x){
                y *= 10;
                y += x % 10;
                x /= 10;
            }
            return y;
        };
        int ans = INT_MAX;
        std::unordered_map<int, int> index;
        for (int i = 0; i < nums.size(); i++){
            if (index.find(nums[i]) != index.end())
                ans = min(ans, i - index[nums[i]]);
            index[reverse(nums[i])] = i;
        }
        // index.clear();
        // for (int i = nums.size() - 1; i >= 0; i++){
        //     if (index.find(nums[i]) != index.end())
        //         ans = min(ans, index[nums[i]] - i);
        //     index[reverse(nums[i])] = i;
        // }
        return ans == INT_MAX ? -1 : ans;
    }
};