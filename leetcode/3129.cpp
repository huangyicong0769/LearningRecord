#include "lc.hpp"

class Solution2 {
    const int M = 1e9 + 7;
public:
    int numberOfStableArrays(int zero, int one, int limit) {
        if (zero == 0 && one == 0) {
            return 1;
        }

        const int W = limit + 1;
        auto idx = [W](int usedZero, int streak) {
            return usedZero * W + streak;
        };

        vector<int> f0((zero + 1) * W, 0), f1((zero + 1) * W, 0);
        vector<int> g0((zero + 1) * W, 0), g1((zero + 1) * W, 0);

        if (zero > 0) {
            f0[idx(1, 1)] = 1;
        }
        if (one > 0) {
            f1[idx(0, 1)] = 1;
        }

        for (int i = 2; i <= zero + one; i++) {
            fill(g0.begin(), g0.end(), 0);
            fill(g1.begin(), g1.end(), 0);

            const int jl = max(0, i - one);
            const int jr = min(zero, i);
            for (int j = jl; j <= jr; j++) {
                const int k0Max = min(limit, j);
                const int k1Max = min(limit, i - j);

                if (j > 0) {
                    for (int k = 2; k <= k0Max; k++) {
                        g0[idx(j, k)] = f0[idx(j - 1, k - 1)];
                    }
                    int &sumFromOne = g0[idx(j, 1)];
                    for (int k = 1; k <= k1Max; k++) {
                        sumFromOne += f1[idx(j - 1, k)];
                        sumFromOne %= M;
                    }
                }

                if (i - j > 0) {
                    for (int k = 2; k <= k1Max; k++) {
                        g1[idx(j, k)] = f1[idx(j, k - 1)];
                    }
                    int &sumFromZero = g1[idx(j, 1)];
                    for (int k = 1; k <= k0Max; k++) {
                        sumFromZero += f0[idx(j, k)];
                        sumFromZero %= M;
                    }
                }
            }

            swap(f0, g0);
            swap(f1, g1);
        }

        int ans = 0;
        for (int k = 1; k <= min(limit, zero); k++) {
            ans += f0[idx(zero, k)];
            ans %= M;
        }
        for (int k = 1; k <= min(limit, one); k++) {
            ans += f1[idx(zero, k)];
            ans %= M;
        }
        return ans;
    }
};

class Solution1 {
    const int M = 1e9 + 7;
public:
    int numberOfStableArrays(int zero, int one, int limit) {
        vector f(zero + 1, vector<vector<int>>(2, vector<int>(limit + 1)));
        vector g(zero + 1, vector<vector<int>>(2, vector<int>(limit + 1)));

        f[1][0][1] = 1;
        f[0][1][1] = 1;

        // auto print = [](vector<vector<vector<int>>> v){
        //     for (auto &grid : v){
        //         for (int k = 0; k < grid[0].size(); k++)
        //             printf("(%d, %d), ", grid[0][k], grid[1][k]);
        //         cout << endl;
        //     }
        //     cout << "===" << endl;
        // };

        for (int i = 2; i <= zero + one; i++){
            for (auto &v2 : g)
                for (auto &v1 : v2)
                    std::fill(v1.begin(), v1.end(), 0);
            for (int j = 0; j <= min(zero, i); j++){
                for (int k = 1; k <= min(limit, i); k++){
                    // printf("%d, %d, %d:\n", i, j, k);
                    if (j > 0) {
                        g[j][0][k] += f[j - 1][0][k - 1];
                        g[j][0][k] %= M;
                        g[j][0][1] += f[j - 1][1][k];
                        g[j][0][1] %= M;
                    }
                    g[j][1][k] += f[j][1][k - 1];
                    g[j][1][k] %= M;
                    g[j][1][1] += f[j][0][k];
                    g[j][1][1] %= M;
                }
            }
            swap(f, g);
            // print(f);
        }
        int ans = 0;
        for (int k1 = 0; k1 < 2; k1++)
            for (int k2 = 1; k2 <= limit; k2++){
                ans += f[zero][k1][k2];
                ans %= M;
            }
        return ans;
    }
};