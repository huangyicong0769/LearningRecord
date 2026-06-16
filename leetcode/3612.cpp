#include "lc.hpp"

class Solution {
public:
    string processStr(string s) {
        string res;
        for (char c : s) {
            if (c == '*'){
                if (!res.empty())
                    res.pop_back();
            } else if (c == '#'){
                res.append(res);
            } else if (c == '%'){
                std::reverse(res.begin(), res.end());
            } else {
                res.push_back(c);
            }
        }
        return res;
    }
};