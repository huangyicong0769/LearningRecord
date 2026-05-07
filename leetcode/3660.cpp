#include "lc.hpp"

class Solution {
public:
    vector<int> maxValue(vector<int>& nums) {
        const int N = nums.size();
        std::vector<int> ans = nums;
        
        int tmp = ans[0];
        for (int i = 1; i < N; i++){
            if (tmp < ans[i]){
                tmp = ans[i];
            }else{
                ans[i] = tmp;
            }
        }

        std::map<int, int> h;
        h.insert({nums[N - 1], N - 1});
        for (int i = N - 2; i >= 0; i--){
            auto it = h.lower_bound(ans[i]);
            if (it != h.begin()) {
                auto [_, j] = *(std::prev(it));
                ans[i] = max(ans[i], ans[j]);
            }
            h.insert({nums[i], i});
        }
        return ans;
    }
};