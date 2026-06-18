#include "lc.hpp"

class Solution {
public:
    double angleClock(int hour, int minutes) {
        double a1 =  360.0 * hour / 12.0 + 30.0 * minutes / 60.0;
        double a2 = 360.0 * minutes / 60.0;
        double d1 = abs(a1 - a2);
        double d2 = 360.0 - d1;
        return min(d1, d2);
    }
};