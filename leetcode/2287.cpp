#include "lc.hpp"

class Solution {
public:
    int rearrangeCharacters(string s, string target) {
        std::vector<int> countS(26), countT(26);
        for (char c : s) {
            countS[c - 'a']++;
        }
        for (char c : target) {
            countT[c - 'a']++;
        }
        int result = INT_MAX;
        for (int i = 0; i < 26; ++i) {
            if (countT[i] > 0) {
                result = std::min(result, countS[i] / countT[i]);
            }
        }
        return result;
    }
};