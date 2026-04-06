#include "lc.hpp"

class Solution {
    const int di[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    std::unordered_map<int, vector<int>> line_obstacles, col_obstacles; 
public:
    int robotSim(vector<int>& commands, vector<vector<int>>& obstacles) {
        for (const auto &obstacle : obstacles){
            const auto & x = obstacle[0], y = obstacle[1];
            line_obstacles[y].push_back(x);
            col_obstacles[x].push_back(y);
        }
        for (auto &[_, line]:line_obstacles)
            std::sort(line.begin(), line.end());
        for (auto &[_, col]:col_obstacles)
            std::sort(col.begin(), col.end());
        auto robot = std::make_tuple(0, 0, 0);
        int ans = 0;
        for (const auto &opt : commands){
            auto & [x, y, k] = robot;
            if (opt == -1){
                k = (k + 1)%4;
            }else if (opt == -2){
                k = (k - 1 + 4) % 4;
            } else {
                auto nx = x, ny = y;
                if (k == 0){
                    ny += opt;
                    if (col_obstacles.find(x) != col_obstacles.end()){
                        const auto &v = col_obstacles[x];
                        auto it = std::upper_bound(v.begin(), v.end(), y);
                        if (it != v.end()){
                            ny = min(ny, *it - 1);
                        }
                    }
                } else if (k == 1){
                    nx += opt;
                    if (line_obstacles.find(y) != line_obstacles.end()){
                        const auto &v = line_obstacles[y];
                        auto it = std::upper_bound(v.begin(), v.end(), x);
                        if (it != v.end()){
                            nx = min(nx, *it - 1);
                        }
                    }
                } else if (k == 2){
                    ny -= opt;
                    if (col_obstacles.find(x) != col_obstacles.end()){
                        const auto &v = col_obstacles[x];
                        auto it = std::lower_bound(v.begin(), v.end(), y);
                        if (it != v.begin()){
                            ny = max(ny, *(std::prev(it)) + 1);
                        }
                    }

                } else if (k == 3){
                    nx -= opt;
                    if (line_obstacles.find(y) != line_obstacles.end()){
                        const auto &v = line_obstacles[y];
                        auto it = std::lower_bound(v.begin(), v.end(), x);
                        if (it != v.begin()){
                            nx = max(nx, *(std::prev(it)) + 1);
                        }
                    }
                }
                x = nx;
                y = ny;
                ans = max(ans, x*x + y*y);
            }
        }
        return ans;
    }
};