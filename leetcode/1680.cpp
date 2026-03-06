#include "lc.hpp"

class Solution {
    const int M = 1e9 + 7;
public:
    int concatenatedBinary(int n) {
        auto bitlen = [](int x) -> auto {
            int ret = 0;
            while (x){
                ret++;
                x /= 2;
            }
            return ret;
        };
        long long ans = 0;
        for (int i = 1; i <= n; i++){
            ans = ((ans << bitlen(i)) + i) % M;
        }
        return static_cast<int>(ans);
    }
};