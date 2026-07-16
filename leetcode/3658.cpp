#include "lc.hpp"

class Solution {
public:
    int gcdOfOddEvenSums(int n) {
        return std::gcd((1 + 2 * n - 1), (2 + 2 * n - 2));
    }
};