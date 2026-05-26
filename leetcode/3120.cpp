#include "lc.hpp"

class Solution {
public:
    int numberOfSpecialChars(string word) {
        std::vector<char> h(128);
        for (const char &ch : word)
            h[ch] = 1;
        int ans = 0;
        for (int i = 'A'; i <= 'Z'; i++){
            ans += h[i] && h[i - 'A' + 'a'];
        }
        return ans;
    }
};