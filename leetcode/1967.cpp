#include "lc.hpp"

class Solution {
public:
    int numOfStrings(vector<string>& patterns, string word) {
        int ans = 0;
        for (const auto& p: patterns)
            if (word.find(p) != std::string::npos)
                ans++;
        return ans;
    }
};