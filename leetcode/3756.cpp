#include "lc.hpp"

class Solution {
    constexpr static int MOD = 1e9 + 7;
public:
    vector<int> sumAndMultiply(string s, vector<vector<int>>& queries) {
        const int N = s.size();
        std::vector<int> preSum(N, 0), preX(N, 0), preNum(N, 0), prePow10(N, 1);
        preSum[0] = s[0] - '0';
        preX[0] = s[0] - '0';
        preNum[0] = s[0] != '0';
        for (int i = 1; i < N; ++i) {
            if (s[i] != '0') {
                preX[i] = (10LL * preX[i - 1] + (s[i] - '0')) % MOD;
                preNum[i] = preNum[i - 1] + 1;
            } else {
                preX[i] = preX[i - 1];
                preNum[i] = preNum[i - 1];
            }
            prePow10[i] = (10LL * prePow10[i - 1]) % MOD;
            preSum[i] = (preSum[i - 1] + (s[i] - '0')) % MOD;
        }
        std::vector<int> result;
        for (const auto& q:queries) {
            const int l = q[0], r = q[1];
            const int sum = (preSum[r] - (l > 0 ? preSum[l - 1] : 0) + MOD) % MOD;
            const int x = (preX[r] - (l > 0 ? (1LL * preX[l - 1] * prePow10[preNum[r] - preNum[l - 1]]) % MOD : 0) + MOD) % MOD;
            result.push_back((1LL * sum * x) % MOD);
        }
        return result;
    }
};