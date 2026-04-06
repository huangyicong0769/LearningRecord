#include "lc.hpp"

class Solution {
public:
    bool judgeCircle(string moves) {
        int line = 0, col = 0;
        for (const char & opt:moves){
            if (opt == 'U') line++;
            else if (opt == 'D') line--;
            else if (opt == 'R') col++;
            else col--;
        }
        return line == 0 && col == 0;
    }
};