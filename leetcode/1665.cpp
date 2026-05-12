#include "lc.hpp"

class Solution {
public:
    int minimumEffort(vector<vector<int>>& tasks) {
        int ans = 0;

        sort(tasks.begin(), tasks.end(), [](const vector<int> &a, const vector<int> &b)->bool {
            return a[1] - a[0] < b[1] - b[0];
        });

        for (const auto& t : tasks) {
            ans = max(ans + t[0], t[1]);
        }
        return ans;
    }
};