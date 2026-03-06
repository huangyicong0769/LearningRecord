#include "lc.hpp"

class Solution {
public:
    int minOperations(string s) {
        int st[2]={0};
        for (int i = 0; i < s.size(); i++)
            st[(i % 2) ^ (s[i] - '0')]++;
        return min(st[0], st[1]);
    }
};