#include "lc.hpp"

class Solution {
public:
    bool checkOnesSegment(string s) {
        int cnt = 0, state = 0;
        for (char ch : s){
            cnt += state == 0 && ch == '1';
            if (cnt > 1)
                return false;
            state = ch - '0';
        }
        return true;
    }
};