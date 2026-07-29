#include "lc.hpp"

class Solution {
public:
    string smallestPalindrome(string s) {
        string ans = s.substr(0, s.size() / 2);
        std::sort(ans.begin(), ans.end());
        return ans + (s.size() % 2 == 1 ? string(1, s[s.size() / 2]) : "") + string(ans.rbegin(), ans.rend());
    }
};