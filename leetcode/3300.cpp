#include "lc.hpp"

class Solution {
public:
    int minElement(vector<int>& nums) {
        return std::ranges::min(nums | std::views::transform([](int x){
            int y = 0;
            while (x){
                y += x % 10;
                x /= 10;
            }
            return y;
        }));
    }
};