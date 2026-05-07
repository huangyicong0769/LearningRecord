#include "lc.hpp"

class Solution {
public:
    bool rotateString(string s, string goal) {
        if (s.size() != goal.size()) return false;
        s.append(s.begin(), s.end());
        return s.find(goal) != string::npos;
    }
};