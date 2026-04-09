// Also for 3653
#include "lc.hpp"

class Solution {
    static const int M = 1e9 + 7;

    int pow(int a, int x = M - 2){
        if (x == 0) return 1;
        if (x == 1) return a;
        int tmp = pow(a, x >> 1);
        return static_cast<int>(1LL * tmp * tmp % M * (x % 2 ? a : 1) % M);
    }

public:
    int xorAfterQueries(vector<int>& nums, vector<vector<int>>& queries) {
        const int N = nums.size();
        const int B = sqrt(N);
        std::unordered_map<int, std::unordered_map<int, vector<int>>> qs;
        for (const auto &q : queries){
            const int &l = q[0], &r = q[1], &k = q[2], &v = q[3];
            if (k >= B){
                for (int i = l; i <= r; i += k)
                    nums[i] = 1LL * nums[i] * v % M;
            }else {
                const int idx = l % k;
                if (qs[k].find(idx) == qs[k].end())
                    qs[k][idx].assign(N/k + 2, 1);
                qs[k][idx][l / k] = 1LL * qs[k][idx][l / k] * v % M;
                qs[k][idx][(r - idx) / k + 1] = 1LL * qs[k][idx][(r - idx) / k + 1] * pow(v) % M;
            }
        }
        for (const auto &[k, s]:qs){
            for (const auto &[idx, vs] : s){
                long long cur = 1;
                for (int i = 0; idx + i * k < N; i++){
                    cur = cur * vs[i] % M;
                    nums[idx + i * k] = cur * nums[idx + i * k] % M;
                }
            }
        }
        int ans = nums[0];
        for (int i = 1; i < nums.size(); i++)
            ans ^= nums[i];
        return ans;
    }
};