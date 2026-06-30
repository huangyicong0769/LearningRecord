#include "lc.hpp"

class Solution {
public:
    int numberOfSubstrings(string s) {
        std::vector<int> h[3];
        for (int i = 0; i < s.size(); i++)
            h[s[i] - 'a'].push_back(i);
        int ans = 0;
        int a = 0, b = 0, c = 0;
        for (int i = 0; i < s.size(); i++){
            while (a < h[0].size() && h[0][a] < i) a++;
            while (b < h[1].size() && h[1][b] < i) b++;
            while (c < h[2].size() && h[2][c] < i) c++;
            if (a == h[0].size() || b == h[1].size() || c == h[2].size()) break;
            ans += s.size() - std::max({h[0][a], h[1][b], h[2][c]});
        }
        return ans;
    }
};