#include "lc.hpp"

class Solution {
    static constexpr int M = 1e9 + 7;
private:
    using Matrix = vector<vector<int>>;

    Matrix mul(const Matrix& a, const Matrix& b) {
        int n = a.size();
        int m = b[0].size();
        Matrix res(n, vector<int>(m, 0));

        for (int i = 0; i < n; i++) {
            for (int k = 0; k < a[0].size(); k++) {
                int r = a[i][k];
                if (r == 0) {
                    continue;
                }
                for (int j = 0; j < m; j++) {
                    res[i][j] = (res[i][j] + 1LL * r * b[k][j] % M) % M;
                }
            }
        }
        return res;
    }

    Matrix powMul(Matrix base, int exp, Matrix res) {
        while (exp > 0) {
            if (exp & 1) {
                res = mul(res, base);
            }
            base = mul(base, base);
            exp >>= 1;
        }
        return res;
    }

public:
    int zigZagArrays(int n, int l, int r) {
        const int m = r - l + 1;
        Matrix u(m, vector<int>(m, 0));

        for (int j = 1; j < m; j++)
            for (int i = m - j; i < m; i++)
                u[i][j] = 1;

        Matrix dp(1, vector<int>(m, 1));

        dp = powMul(u, n - 1, dp);

        int ans = 0;
        for (int i = 0; i < m; i++) {
            ans = (ans + dp[0][i]) % M;
        }

        return ans * 2 % M;
    }
};