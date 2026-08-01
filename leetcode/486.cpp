#include "lc.hpp"

class Solution {
    std::vector<std::vector<int>> f;
    std::vector<std::vector<char>> g;

    int dfs(const std::vector<int>&nums, int l, int r) {
        if (g[l][r]) return f[l][r];
        g[l][r] = 1;
        if (l == r) return f[l][r] = nums[l];
        return f[l][r] = std::max(nums[l] - dfs(nums, l + 1, r), nums[r] - dfs(nums, l, r - 1));
    }
public:
    bool predictTheWinner(vector<int>& nums) {
        int n = nums.size();
        f.assign(n, std::vector<int>(n));
        g.assign(n, std::vector<char>(n));
        return dfs(nums, 0, n - 1) >= 0;
    }
};