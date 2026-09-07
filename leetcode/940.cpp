#include "lc.hpp"

class Solution {
    const int MOD = 1e9 + 7;
public:
    int distinctSubseqII(string s) {
        std::array<int, 26> f{};
        int ans = 1;
        for (char c : s){
            int x = c - 'a';
            int t = ans;
            ans = (ans * 2LL - f[x] + MOD) % MOD;
            f[x] = t;
        }
        return (ans - 1 + MOD) % MOD;
    }
};