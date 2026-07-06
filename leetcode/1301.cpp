#include "lc.hpp"

class Solution {
    constexpr static int MOD = 1e9 + 7;
public:
    vector<int> pathsWithMaxScore(vector<string>& board) {
        const int n = board.size();
        std::vector<int> f1(n, 0), g1(n, 0), f2(n, 0), g2(n, 0);
        f1[0] = 0; f2[0] = 1;
        for (int j = 1; j < n; j++){
            if (board[0][j] == 'X') break;
            f1[j] = f1[j - 1] + (board[0][j] - '0');
            f2[j] = 1;
        }
        for (int i = 1; i < n; i++){
            std::swap(f1, g1);
            std::swap(f2, g2);
            f1[0] = f2[0] = 0;
            if (board[i][0] != 'X' && g2[0] > 0){
                f1[0] = g1[0] + (board[i][0] - '0');
                f2[0] = g2[0];
            }
            for (int j = 1; j < n; j++){
                f1[j] = f2[j] = 0;
                if (board[i][j] == 'X') continue;
                int max_score = std::max({g1[j], f1[j - 1], g1[j - 1]});
                if (max_score == g1[j] && g2[j] > 0) f2[j] = (f2[j] + g2[j]) % MOD;
                if (max_score == f1[j - 1] && f2[j - 1] > 0) f2[j] = (f2[j] + f2[j - 1]) % MOD;
                if (max_score == g1[j - 1] && g2[j - 1] > 0) f2[j] = (f2[j] + g2[j - 1]) % MOD;
                f1[j] = f2[j] > 0 ? max_score + (board[i][j] - '0') : 0;
            }
        }
        return {f1[n - 1] - (f2[n - 1] ? 'S' - '0' : 0), f2[n - 1]};
    }
};