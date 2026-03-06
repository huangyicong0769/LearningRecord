#include "lc.hpp"

class Solution {
public:
    int numSteps(string s) {
        int ans = 0, y = 0;
        for (char ch : s | std::views::drop(1) | std::views::reverse){
            int x = (ch - '0') ^ y ;
            y &= (ch - '0');
            if (x){
                ans++;
                y = 1;
            }
            ans++;
        }
        return ans + y;
    }
};