#include "lc.hpp"

class Solution1 {
public:
    int minRemoval(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int ans = 0;        
        auto check = [&](int l) -> bool {
            if (l == 1) 
                return true;
            for (int i = 0; i + l - 1 < nums.size(); i++){
                if (1LL * nums[i] * k >= 1LL * nums[i + l - 1])
                    return true;
            }
            return false;
        };
        for (int l = 0, r = nums.size() - 1; l <= r;){
            int mid = (l + r) / 2;
            if (check(nums.size() - mid)){
                ans = mid;
                r = mid - 1;
            }else
                l = mid + 1;
        }
        return ans;
    }
};

class Solution2 {
public:
    int minRemoval(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int ans = nums.size();
        for (int i = 0, j = 0; i < nums.size(); i++){
            while (j < nums.size() && 1LL * nums[i] * k <= nums[j])
                j++;
            ans = min(ans, (int)nums.size() - (j - i));
        }
        return ans;
    }
};