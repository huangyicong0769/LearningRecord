#include "lc.hpp"

class Solution {
public:
    string smallestSubsequence(string s) {
        vector<int> lastIndex(26, -1);
        for (int i = 0; i < s.size(); ++i) {
            lastIndex[s[i] - 'a'] = i;
        }
        vector<bool> seen(26, false);
        string result;
        for (int i = 0; i < s.size(); ++i) {
            int c = s[i] - 'a';
            if (seen[c]) continue;
            while (!result.empty() && result.back() > s[i] && lastIndex[result.back() - 'a'] > i) {
                seen[result.back() - 'a'] = false;
                result.pop_back();
            }
            result.push_back(s[i]);
            seen[c] = true;
        }
        return result;
    }
};