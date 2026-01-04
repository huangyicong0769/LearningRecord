class Solution {
    const int M = 1e9 + 7;
    bool adjust(int i, int k1, int k2, int k3){
        switch (i % 3){
            case 0:
                return k1 == k2 || k2 == k3;
            case 1:
                return k2 == k3;
            case 2:
                return k1 == k2;
        }
        return false;
    }
public:
    int numOfWays(int n) {
        // if (n == 1) return 12;
        int f[2][3][3][3];
        int x = 0, y = 1;
        for (int k1 = 0; k1 < 3; k1++)
            for (int k2 = 0; k2 < 3; k2++)
                for (int k3 = 0; k3 < 3; k3++){
                    if (k1 == k2 || k2 == k3) f[x][k1][k2][k3] = 0;
                    else f[x][k1][k2][k3] = 1;
                }
        for (int i = 4; i <= 3*n; i++){
            for (int k1 = 0; k1 < 3; k1++)
                for (int k2 = 0; k2 < 3; k2++)
                    for (int k3 = 0; k3 < 3; k3++){
                        f[y][k1][k2][k3] = 0;
                        for (int k4 = 0; k4 < 3; k4++){
                            if (adjust(i, k1, k2, k3) || k1 == k4) continue;
                            f[y][k1][k2][k3] += f[x][k2][k3][k4];
                            f[y][k1][k2][k3] %= M;
                        }
                    }
            x ^= 1;
            y ^= 1;
        }
        int ans = 0;
        for (int k1 = 0; k1 < 3; k1++)
            for (int k2 = 0; k2 < 3; k2++)
                for (int k3 = 0; k3 < 3; k3++){
                    if (k1 == k2 || k2 == k3) continue;
                    ans += f[x][k1][k2][k3];
                    ans %= M;
                }
        return ans;
    }
};

//printf("f[%d][%d][%d]=%d\n", k1, k2, k3, f[3][k1][k2][k3]);