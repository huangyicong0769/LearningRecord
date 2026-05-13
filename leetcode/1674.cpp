#include "lc.hpp"

class Solution {
public:
    int minMoves(vector<int>& nums, int limit) {
        const int N = nums.size();
        vector<int> cnt(2 * limit + 2);
        for (int i = 0; i < N / 2; ++i){
            int a = min(nums[i], nums[N - 1 - i]),
                b = max(nums[i], nums[N - 1 - i]);
            cnt[2] += 2;
            cnt[a + 1] -= 1;
            cnt[a + b] -= 1;
            cnt[a + b + 1] += 1;
            cnt[b + limit + 1] += 1;
        }
        int ans = N;
        for (int i = 2, sum = 0; i <= 2 * limit; ++i) {
            sum += cnt[i];
            ans = min(ans, sum);
        }
        return ans;
    }
};