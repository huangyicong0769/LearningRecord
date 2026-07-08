#include "lc.hpp"

class Solution {
public:
    long long sumAndMultiply(int n) {
        long long sum1 = 0, sum2 = 0,product = 1;
        for (int x = n; x > 0; x /= 10) {
            const int a = x % 10;
            if (a == 0) continue;
            sum1 += a;
            sum2 += a * product;
            product *= 10;
        }
        return sum1 * sum2;   
    }
};