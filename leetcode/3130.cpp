#include "lc.hpp"

class Solution {
    const int M = 1e9 + 7;
public:
    int numberOfStableArrays(int zero, int one, int limit) {
        const int cols = one + 1;
        const int total = (zero + 1) * cols;
        vector<int> endWithZero(total, 0), endWithOne(total, 0);

        auto idx = [&](int i, int j) { return i * cols + j; };
        auto addMod = [&](int a, int b) {
            a += b;
            if (a >= M) a -= M;
            return a;
        };
        auto subMod = [&](int a, int b) {
            a -= b;
            if (a < 0) a += M;
            return a;
        };

        for (int i = 1; i <= min(zero, limit); ++i) endWithZero[idx(i, 0)] = 1;
        for (int j = 1; j <= min(one, limit); ++j) endWithOne[idx(0, j)] = 1;

        for (int i = 1; i <= zero; ++i) {
            for (int j = 1; j <= one; ++j) {
                int waysZero = addMod(endWithZero[idx(i - 1, j)], endWithOne[idx(i - 1, j)]);
                if (i > limit) waysZero = subMod(waysZero, endWithOne[idx(i - limit - 1, j)]);
                endWithZero[idx(i, j)] = waysZero;

                int waysOne = addMod(endWithZero[idx(i, j - 1)], endWithOne[idx(i, j - 1)]);
                if (j > limit) waysOne = subMod(waysOne, endWithZero[idx(i, j - limit - 1)]);
                endWithOne[idx(i, j)] = waysOne;
            }
        }

        return addMod(endWithZero[idx(zero, one)], endWithOne[idx(zero, one)]);
    }
};