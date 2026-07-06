#include "lc.hpp"

class Solution {
public:
    int removeCoveredIntervals(vector<vector<int>>& intervals) {
        std::sort(intervals.begin(), intervals.end(), [](const auto& a, const auto& b) {
            return a[0] == b[0] ? a[1] > b[1] : a[0] < b[0];
        });
        int ans = 0, r = -1;
        for (const auto& interval : intervals) {
            if (interval[1] <= r)
                continue;
            r = interval[1];
            ++ans;
        }
        return ans;
    }
};