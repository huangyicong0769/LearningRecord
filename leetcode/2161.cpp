#include "lc.hpp"

class Solution {
public:
    vector<int> pivotArray(vector<int>& nums, int pivot) {
        std::vector<int> less, equal, greater;
        for (int num : nums) {
            if (num < pivot) {
                less.push_back(num);
            } else if (num == pivot) {
                equal.push_back(num);
            } else {
                greater.push_back(num); 
            }
        }
        return std::ranges::to<std::vector<int>>(std::array{std::span{less}, std::span{equal}, std::span{greater}} | std::views::join);
    }
};