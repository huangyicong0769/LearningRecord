#include "lc.hpp"

class Solution {
public:
    char findKthBit(int n, int k) {
        return find(n, k, 1) + '0';
    }
    int find(int n, int k, int flag) {
        if (n == 1)
            return 0;
        int x = (1 << (n - 1));
        if (k == x)
            return flag;
        else if (k < x)
            return find(n - 1, k, 1);
        else
            return find(n - 1, k - x, 0);
    }
};