#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
    int minimumDeleteSum(string s1, string s2) {
        const int &n = s1.size(), &m = s2.size();
        std::vector<std::vector<int>> f(2, std::vector<int>(m + 1));
        int x = 0, y = 1;
        for (int j = 1; j <= m; j++) f[x][j] = f[x][j - 1] + s2[j - 1];
        for (int i = 0; i < n; i++){
            f[y][0] = f[x][0] + s1[i];
            for (int j = 0; j < m; j++){
                f[y][j + 1] = min(f[x][j + 1] + s1[i], f[y][j] + s2[j]);
                if (s1[i] == s2[j])
                    f[y][j + 1] = min(f[y][j + 1], f[x][j]);
            }
            x^=1;
            y^=1;
        }
        // auto printF = [&](){
        //     for (int i = 0; i <= n; ++i) {
        //         for (int j = 0; j <= m; ++j) {
        //             cout << f[i][j] << (j == m ? '\n' : ' ');
        //         }
        //     }
        // };
        // printF();
        return f[x][m];
    }
};