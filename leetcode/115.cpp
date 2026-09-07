#include "lc.hpp"

class Solution {
public:
    int numDistinct(string s, string t) {
        const int M = s.size(), N = t.size();
        std::vector<int> f(N + 1);
        f[0] = 1;
        for (int i = 1; i <= M; i++){
            for (int j = std::min(i, N); j > 0; j--)
                if (s[i - 1] == t[j - 1])
                    f[j] = std::min<long long>(1LL * f[j] + f[j - 1], INT_MAX);
        }
        return f[N];
    }
};