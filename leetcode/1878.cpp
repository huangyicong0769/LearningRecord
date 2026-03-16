#include "lc.hpp"

class Solution {
    const int d[4][2] = {{-1, -1}, {-1, 1}, {1, 1}, {1, -1}};
public:
    vector<int> getBiggestThree(vector<vector<int>>& grid) {
        const int N = grid.size(), M = grid[0].size();
        set<int> heap;
        vector sums(N, vector<vector<int>>(M, vector<int>(2)));

        auto getidx = [&](int i, int j, int k){
            if (i < 0 || j < 0 || i >= N || j >= M)
                return 0;
            return sums[i][j][k];
        };

        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++){
                for (int k = 0; k < 2; k++){
                    int x = i + d[k][0],
                        y = j + d[k][1];
                    sums[i][j][k] = getidx(x, y, k) + grid[i][j];
                }
                if ((heap.size() < 3 || *heap.begin() < grid[i][j]) && heap.find(grid[i][j]) == heap.end()){
                    if (heap.size() == 3) 
                        heap.erase(heap.begin());
                    heap.insert(grid[i][j]);
                }
            }

        for (int l = min(N, M) / 2; l > 0; l--){
            for (int x1 = 0; x1 < N - 2 * l; x1++)
                for (int y1 = l; y1 < M - l; y1++){
                    int tmp = 0;
                    int x2 = x1 + 2 * l;
                    #define y2 y1
                    for (int k = 0; k < 2; k++){
                        int x3 = x2 + d[k][0]*l,
                            y3 = y2 + d[k][1]*l;
                        tmp += sums[x2][y2][k] - getidx(x3, y3, k);
                        tmp += sums[x3][y3][k ^ 1] - getidx(x1, y1, k ^ 1);
                    }
                    tmp += grid[x1][y1] - grid[x2][y2];
                    // printf("%d : (%d, %d) = %d\n", l, x1, y1, tmp);
                    if ((heap.size() < 3 || *heap.begin() < tmp) && heap.find(tmp) == heap.end()){
                        if (heap.size() == 3) 
                            heap.erase(heap.begin());
                        heap.insert(tmp);
                    }
                }
        }
        vector<int> ans;
        while(heap.size()){
            ans.push_back(*prev(heap.end()));
            heap.erase(prev(heap.end()));
        }
       return ans;
    }
};

class SolutionOptimized {
public:
    vector<int> getBiggestThree(vector<vector<int>>& grid) {
        const int n = (int)grid.size();
        const int m = (int)grid[0].size();

        // dl: main diagonal prefix (\), dr: anti-diagonal prefix (/)
        vector<vector<int>> dl(n + 1, vector<int>(m + 1, 0));
        vector<vector<int>> dr(n + 1, vector<int>(m + 2, 0));

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                dl[i + 1][j + 1] = dl[i][j] + grid[i][j];
                dr[i + 1][j] = dr[i][j + 1] + grid[i][j];
            }
        }

        array<int, 3> top = {INT_MIN, INT_MIN, INT_MIN};

        auto pushTop3Distinct = [&](int x) {
            if (x == top[0] || x == top[1] || x == top[2]) return;
            if (x > top[0]) {
                top[2] = top[1];
                top[1] = top[0];
                top[0] = x;
            } else if (x > top[1]) {
                top[2] = top[1];
                top[1] = x;
            } else if (x > top[2]) {
                top[2] = x;
            }
        };

        auto sumMainDiag = [&](int x1, int y1, int x2, int yy2) {
            // cells on (x1,y1) -> (x2,y2), x and y both increase
            return dl[x2 + 1][yy2 + 1] - dl[x1][y1];
        };

        auto sumAntiDiag = [&](int x1, int y1, int x2, int yy2) {
            // cells on (x1,y1) -> (x2,y2), x increases and y decreases
            return dr[x2 + 1][yy2] - dr[x1][y1 + 1];
        };

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                pushTop3Distinct(grid[i][j]);

                const int maxLen = min({i, n - 1 - i, j, m - 1 - j});
                for (int len = 1; len <= maxLen; ++len) {
                    const int topX = i - len, topY = j;
                    const int rightX = i, rightY = j + len;
                    const int bottomX = i + len, bottomY = j;
                    const int leftX = i, leftY = j - len;

                    int s = 0;
                    s += sumMainDiag(topX, topY, rightX, rightY);          // top -> right
                    s += sumAntiDiag(rightX, rightY, bottomX, bottomY);    // right -> bottom
                    s += sumMainDiag(leftX, leftY, bottomX, bottomY);      // left -> bottom
                    s += sumAntiDiag(topX, topY, leftX, leftY);            // top -> left

                    // Four vertices are counted twice; keep each once.
                    s -= grid[topX][topY] + grid[rightX][rightY] + grid[bottomX][bottomY] + grid[leftX][leftY];
                    pushTop3Distinct(s);
                }
            }
        }

        vector<int> ans;
        for (int x : top) {
            if (x != INT_MIN) ans.push_back(x);
        }
        return ans;
    }
};