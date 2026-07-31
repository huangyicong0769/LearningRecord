#include "lc.hpp"

class Solution {
public:
    int minimumPushes(string word) {
        std::vector<int> freq(26, 0);
        for (char c : word)
            ++freq[c - 'a'];

        std::ranges::sort(freq, std::greater<>());

        int ans = 0;
        for (int i = 0; i < 26; ++i)
            ans += freq[i] * (i / 8 + 1);

        return ans;
    }
};