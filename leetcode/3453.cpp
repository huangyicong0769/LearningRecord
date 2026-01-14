#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    double separateSquares(vector<vector<int>>& squares) {
        long long s = 0;
        std::vector<std::tuple<int, int, int>> lines;
        for (const auto &square:squares){
            s += 1LL * square[2] * square[2];
            lines.push_back({square[1], square[2], 1});
            lines.push_back({square[1] + square[2], square[2], -1});
        }
        
        std::sort(lines.begin(), lines.end(), [](const auto &a, const auto &b){
            return std::get<0>(a) < std::get<0>(b);
        });

        double w = 0, cur_s = 0, last = 0;
        for (const auto &[y, l, f] : lines){
            double new_s = w * (y - last);
            if (2LL * (cur_s + new_s) >= s)
                return last + (s - 2.0 * cur_s) / (2.0 * w);
            w += f * l;
            cur_s += new_s;
            last = y;
        }

        return 0.0;
    }
};