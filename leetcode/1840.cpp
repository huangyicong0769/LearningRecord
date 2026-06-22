#include "lc.hpp"

class Solution {
public:
    int maxBuilding(int n, vector<vector<int>>& restrictions) {
        restrictions.push_back({1, 0});
        const int M = restrictions.size();
        std::sort(restrictions.begin(), restrictions.end(), [](const auto& a, const auto& b) {
            return a[0] < b[0];
        });
        for (int i = 1; i < M; i++) {
            int d = restrictions[i][0] - restrictions[i - 1][0];
            restrictions[i][1] = min(restrictions[i][1], restrictions[i - 1][1] + d);
        }
        for (int i = M - 2; i >= 0; i--) {
            int d = restrictions[i + 1][0] - restrictions[i][0];
            restrictions[i][1] = min(restrictions[i][1], restrictions[i + 1][1] + d);
        }
        int ans = 0;
        for (int i = 1; i < M; i++) {
            int id0 = restrictions[i - 1][0];
            int h0 = restrictions[i - 1][1];
            int id1 = restrictions[i][0];
            int h1 = restrictions[i][1];

            ans = max(ans, (h0 + h1 + id1 - id0) / 2);
        }
        ans = max(ans, restrictions.back()[1] + n - restrictions.back()[0]);
        return ans;
    }
};