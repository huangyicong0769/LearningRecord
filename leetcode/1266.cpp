#include <vector>
#include <cmath>
using namespace std;

class Solution {
public:
    int minTimeToVisitAllPoints(vector<vector<int>>& points) {
        int ans = 0;
        auto dist = [](const auto &a, const auto &b) -> int {
            return max(abs(a[0] - b[0]), abs(a[1] - b[1]));
        };
        for (int i = 1; i < points.size(); i++){
            ans += dist(points[i - 1], points[i]);
        }
        return ans;
    }
};