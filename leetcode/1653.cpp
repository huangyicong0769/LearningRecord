#include "lc.hpp"

class Solution {
public:
    int minimumDeletions(string s) {
        int lb = 0, ra = 0;
        for (char ch : s)
            ra += ch == 'a';
        int ans = ra;
        for (char ch : s){
            if (ch == 'a')
                ra--;
            else
                lb++;
            ans = min(ans, lb + ra);
        }
        return ans;
    }
};