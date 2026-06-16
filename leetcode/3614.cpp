#include "lc.hpp"

class Solution {
public:
    char processStr(string s, long long k) {
        long long l = s.size();
        for (char c : s) {
            if (c == '*'){
                if (l != 0)
                    l--;
            } else if (c == '#'){
                l *= 2;
            } else if (c == '%'){
                // No change in length
            } else {
                l++;
            }
        }
        if (k >= l) 
            return '.';
        for (char c  : std::ranges::views::reverse(s)) {
            if (c == '*'){
                l++;
            } else if (c == '#') {
                l /= 2;
                if (k >= l)
                    k -= l;
            } else if (c == '%') {
                k = l - 1 - k;
            } else {
                l--;
                if (k == l)
                    return c;
            }
        }
        return s[k];
    }
};