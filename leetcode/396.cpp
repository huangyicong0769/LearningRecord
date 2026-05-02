#include "lc.hpp"

class Solution {
public:
    int maxRotateFunction(vector<int>& nums) {
        const int N = nums.size();
        int sum = 0;
        int f = 0;
        for (int i = 0; i < N; i++){
            f += i * nums[i];
            sum += nums[i];
        }
        int ans = f;
        for (int i = N - 1; i >= 0; i--){
            f += sum - N * nums[i];
            ans = max(ans, f);
        }
        return ans;
    }
};