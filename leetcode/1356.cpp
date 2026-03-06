#include "lc.hpp"
#include <bit>

class Solution {
public:
    vector<int> sortByBits(vector<int>& arr) {
        sort(arr.begin(), arr.end(), [](const unsigned int &a, const unsigned int &b)-> bool {
            return std::popcount(a) < std::popcount(b) || std::popcount(a) == std::popcount(b) && a < b;
        });
        return arr;
    }
};