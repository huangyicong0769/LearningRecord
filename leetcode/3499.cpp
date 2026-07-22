#include "lc.hpp"

class Solution {
public:
    int maxActiveSectionsAfterTrade(string s) {
        std::vector<int> v;
        int cnt = 1;
        for (int i = 1; i < s.size(); i++) {
            if (s[i] == s[i - 1]) {
                ++cnt;
            } else {
                v.push_back(cnt);
                cnt = 1;
            }
        }
        v.push_back(cnt);
        int ans = 0, sign = s[0] - '0';
        cnt = 0;
        for (int i = 0; i < v.size(); i++) {
            if (sign){
                if (i >= 1 && i + 1 < v.size()){
                    cnt = std::max(cnt, v[i - 1] + v[i + 1]);
                }
                ans += v[i];
            }
            sign ^= 1;
        }
        return ans + cnt;
    }
};