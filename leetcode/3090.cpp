#include "lc.hpp"

class Solution {
public:
    int maximumLengthSubstring(string s) {
        std::vector<int> f(26, 0);
        int ans = 0;
        for (int l = 0, r = 0; r < s.size(); r++) {
            f[s[r] - 'a']++;
            while (l < r && f[s[r] - 'a'] > 1)
                f[s[l++] - 'a']--;
            ans = std::max(ans, r - l + 1);
        }
        return ans;
    }
};