#include "lc.hpp"

class Solution {
public:
    bool winnerSquareGame(int n) {
        std::vector<char> f(n + 1, false);

        for (int i = 1; i <= n; ++i)
            for (int j = 1; j * j <= i; ++j)
                if (!f[i - j * j]) {
                    f[i] = true;
                    break;
                }

        return f[n];
    }
};