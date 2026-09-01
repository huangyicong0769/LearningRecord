#include "lc.hpp"

class Solution {
    static constexpr std::array<std::pair<int, int>, 4> dist = {{{-1, 0}, {1, 0}, {0, -1}, {0, 1}}};
public:
    int minMoves(vector<string>& classroom, int energy) {
        const int N = classroom.size(), M = classroom[0].size();
        std::unordered_map<int, int> L;
        int x0, y0;
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++) {
                if (classroom[i][j] == 'S') {
                    x0 = i;
                    y0 = j;
                } else if (classroom[i][j] == 'L') {
                    L[i * M + j] = L.size();
                }
            }
        
        int e[20][20][1024];
        std::fill(&e[0][0][0], &e[0][0][0] + 20 * 20 * 1024, -1);
        int step = 0;
        std::queue<std::tuple<int, int, int, int>> q;
        q.push({x0, y0, (1 << L.size()) - 1, energy});
        e[x0][y0][(1 << L.size()) - 1] = energy;
        while (!q.empty()) {
            int sz = q.size();
            while (sz--) {
                auto [x, y, mask, e0] = q.front();
                q.pop();
                if (mask == 0) 
                    return step;
                if (e0 == 0) 
                    continue;
                for (auto [dx, dy] : dist) {
                    int x1 = x + dx, y1 = y + dy;
                    if (x1 < 0 || x1 >= N || y1 < 0 || y1 >= M || classroom[x1][y1] == 'X') 
                        continue;
                    int mask1 = mask;
                    if (classroom[x1][y1] == 'L') 
                        mask1 &= ~(1 << L[x1 * M + y1]);
                    int e1 = e0 - 1;
                    if (classroom[x1][y1] == 'R') 
                        e1 = energy;
                    if (e[x1][y1][mask1] < e1) {
                        e[x1][y1][mask1] = e1;
                        q.push({x1, y1, mask1, e1});
                    }
                }
            }
            step++;
        }
        return -1;
    }
};