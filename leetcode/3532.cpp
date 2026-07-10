#include "lc.hpp"

class Solution {
    std::vector<int> fa;

    int getfa(int x) {
        return fa[x] == x ? x : (fa[x] = getfa(fa[x]));
    }

public:
    vector<bool> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
        fa.assign(n, 0);
        std::iota(fa.begin(), fa.end(), 0);

        for (int i = 1; i < n; ++i) {
            if (nums[i] - nums[i - 1] <= maxDiff) {
                fa[getfa(i)] = getfa(i - 1);
            }
        }
        vector<bool> ans;
        for (const auto& q : queries) {
            ans.push_back(getfa(q[0]) == getfa(q[1]));
        }
        return ans;
    }
};