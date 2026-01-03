#include <vector>
using namespace std;

class Solution {
public:
    int numMagicSquaresInside(vector<vector<int>>& grid) {
        const auto &N = grid.size(), &M = grid[0].size();
        vector<vector<vector<int>>> sums = {vector<vector<vector<int>>>(5, vector<vector<int>>(N, vector<int>(M)))};
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++){
                // sums[0][i][j] = (i > 0 ? sums[0][i - 1][j] : 0) + grid[i][j];
                // sums[1][i][j] = (j > 0 ? sums[1][i][j - 1] : 0) + grid[i][j];
                // sums[2][i][j] = (i > 0 && j > 0 ? sums[2][i - 1][j - 1] : 0) + grid[i][j];
                // sums[3][i][j] = (i > 0 && j < M - 1 ? sums[3][i - 1][j + 1] : 0) + grid[i][j];
                sums[4][i][j] = (i > 0 ? sums[4][i - 1][j] : 0) + 
                                (j > 0 ? sums[4][i][j - 1] : 0) - 
                                (i > 0 && j > 0 ? sums[4][i - 1][j - 1] : 0) + 
                                (grid[i][j] > 9 || grid[i][j] < 1);  
            }
        int ans = 0;
        for (int i = 2; i < N; i++)
            for (int j = 2; j < M; j++)
                if (sums[4][i][j] - (i > 2 ? sums[4][i - 3][j] : 0) - (j > 2 ? sums[4][i][j - 3] : 0) + (i > 2 && j > 2 ? sums[4][i - 3][j - 3] : 0) == 0){
                    // int s[8] = {sums[0][i][j] - (i > 2 ? sums[0][i - 3][j] : 0), sums[0][i][j - 1] - (i > 2 ? sums[0][i - 3][j - 1] : 0), sums[0][i][j - 2] - (i > 2 ? sums[0][i - 3][j - 2] : 0),
                    //             sums[1][i][j] - (j > 2 ? sums[0][i][j - 3] : 0), sums[1][i - 1][j] - (j > 2 ? sums[0][i - 1][j - 3] : 0), sums[1][i - 2][j] - (j > 2 ? sums[0][i - 2][j - 3] : 0),
                    //             sums[2][i][j] - (i > 2 && j > 2 ? sums[2][i - 3][j - 3] : 0),
                    //             sums[3][i][j - 2] - (i > 2 && j < M - 1 ? sums[3][i - 3][j + 1] : 0),};
                    int s[8] = {0};
                    bool cnt = true;
                    int num = 0;
                    for (int k1 = i - 2; k1 <= i; k1++)
                        for (int k2 = j - 2; k2 <= j; k2++){
                            num ^= (1 << (grid[k1][k2] - 1));
                            s[k1 - i + 2] += grid[k1][k2];
                            s[k2 - j + 2 + 3] += grid[k1][k2];
                            if (k1 - i == k2 - j) s[6] += grid[k1][k2];
                            if (k1 + k2 == i + j - 2) s[7] += grid[k1][k2];
                        }
                    for (auto a:s)
                        cnt = (cnt && s[0] == a);
                    cnt = cnt && num == 0b111111111;
                    ans += cnt;
                }
        return ans;
    }
};