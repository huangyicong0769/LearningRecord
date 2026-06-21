#include "lc.hpp"

class Solution {
public:
    int maxIceCream(vector<int>& costs, int coins) {
        std::vector<int> m(std::min(100000, std::ranges::max(costs)) + 1);
        for (int c : costs)
            ++m[c];
        int ans = 0;
        for (int i = 1; i < m.size() && coins >= i; ++i) {
            int buy = std::min(m[i], coins / i);
            ans += buy;
            coins -= buy * i;
        }
        return ans;
    }
};