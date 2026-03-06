#include "lc.hpp"

class Solution {
public:
    int minPartitions(string n) {
        char ans = '0';
        for (auto ch : n)
            ans = max(ch, ans);
        return ans - '0';
        return ranges::max(n) - '0';
    }
};