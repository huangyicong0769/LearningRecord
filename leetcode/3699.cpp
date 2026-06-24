#include "lc.hpp"

class Solution {
    const int M = 1e9 + 7;
public:
    int zigZagArrays(int n, int l, int r) {
        std::vector f(2, std::vector(r - l + 1, 0)), g(2, std::vector(r - l + 1, 1));
        for (int i = 1; i < n; i++){
            f[0][0] = 0;
            for (int j = 1; j <= r - l; j++)
                f[0][j] = (f[0][j - 1] + g[1][j - 1]) % M;
            f[1][r - l] = 0;
            for (int j = r - l - 1; j >= 0; j--)
                f[1][j] = (f[1][j + 1] + g[0][j + 1]) % M;
            std::swap(f, g);
        }
        int ans = 0;
        for (int j = 0; j <= r - l; j++){
            ans = (ans + g[0][j]) % M;
            ans = (ans + g[1][j]) % M;
        }
        return ans;
    }
};

class Solution {
    const int M = 1e9 + 7;
public:
    int zigZagArrays(int n, int l, int r) {
        std::vector f(r - l + 1, 0), g(r - l + 1, 1);
        for (int i = 1; i < n; i++){
            f[0] = 0;
            for (int j = 1; j <= r - l; j++){
                f[j] = (f[j - 1] + g[r - l - j + 1]) % M;
            }
            std::swap(f, g);
        }
        int ans = 0;
        for (int j = 0; j <= r - l; j++){
            ans = (ans + g[j]) % M;
        }
        return ans * 2 % M;
    }
};