#include "lc.hpp"

class Solution {
public:
    int numberOfSpecialChars(string word) {
        std::vector<int> l(26, -1), c(26, -1);
        for (int i = 0; i < word.size(); i++){
            const auto &ch = word[i];
            if ('a' <= ch && ch <= 'z')
                l[ch - 'a'] = max(l[ch - 'a'], i);
            else
                if (c[ch - 'A'] == -1)
                    c[ch - 'A'] = i;
        }
        int ans = 0;
        for (int i = 0; i < 26; i++)
            ans += l[i] != -1 && c[i] != -1 && l[i] < c[i];
        return ans;
    }
};