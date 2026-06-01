#include "lc.hpp"

class Solution {
public:
    int minimumCost(vector<int>& cost) {
        return std::ranges::sort(cost, std::greater<>()),
               std::transform_reduce(cost.begin(), cost.end(), std::views::iota(0).begin(), 0,
                                     std::plus<>(), [](int value, int index) {
                                         return index % 3 == 2 ? 0 : value;
                                     });
    }
};