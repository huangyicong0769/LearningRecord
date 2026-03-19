#include "lc.hpp"

class Solution {
public:
    int numberOfSubmatrices(vector<vector<char>>& grid) {
        const int N = grid.size();
        const int M = grid[0].size();
        vector sumX(M + 1, 0);
        vector sumY(M + 1, 0);
        vector sumXn(M + 1, 0);
        vector sumYn(M + 1, 0);
        int ans = 0;
        for (int i = 0; i < N; i++){
            for (int j = 0; j < M; j++){
                sumXn[j + 1] = sumXn[j] + sumX[j + 1] - sumX[j] + (grid[i][j] == 'X');
                sumYn[j + 1] = sumYn[j] + sumY[j + 1] - sumY[j] + (grid[i][j] == 'Y');
                ans += (sumXn[j + 1] == sumYn[j + 1] && sumXn[j + 1] > 0);
            }
            swap(sumX, sumXn);
            swap(sumY, sumYn);
        }
        return ans;
    }
};

class Solution2 {
public:
    int numberOfSubmatrices(vector<vector<char>>& grid) {
        const int n = grid.size();
        const int m = grid[0].size();
        vector<int> diff(m + 1, 0);
        vector<int> tot(m + 1, 0);
        int ans = 0;
        for (int i = 0; i < n; i++) {
            int prevDiffDiag = 0;
            int prevTotDiag = 0;
            for (int j = 0; j < m; j++) {
                int upDiff = diff[j + 1];
                int upTot = tot[j + 1];
                int delta = 0;
                if (grid[i][j] == 'X') {
                    delta = 1;
                } else if (grid[i][j] == 'Y') {
                    delta = -1;
                }
                diff[j + 1] = diff[j] + upDiff - prevDiffDiag + delta;
                tot[j + 1] = tot[j] + upTot - prevTotDiag + (grid[i][j] != '.');
                ans += (diff[j + 1] == 0 && tot[j + 1] > 0);
                prevDiffDiag = upDiff;
                prevTotDiag = upTot;
            }
        }
        return ans;
    }
};

class Solution3 {
public:
    int numberOfSubmatrices(vector<vector<char>>& grid) {
        const int n = grid.size();
        const int m = grid[0].size();
        vector<int> prevDiff(m + 1, 0);
        vector<int> prevCnt(m + 1, 0);
        vector<int> curDiff(m + 1, 0);
        vector<int> curCnt(m + 1, 0);
        int ans = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                const char cell = grid[i][j];
                curDiff[j + 1] = curDiff[j] + prevDiff[j + 1] - prevDiff[j] + (cell == 'X') - (cell == 'Y');
                curCnt[j + 1] = curCnt[j] + prevCnt[j + 1] - prevCnt[j] + (cell != '.');
                ans += (curDiff[j + 1] == 0 && curCnt[j + 1] > 0);
            }
            swap(prevDiff, curDiff);
            swap(prevCnt, curCnt);
        }
        return ans;
    }
};