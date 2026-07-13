#include "lc.hpp"

class Solution {
public:
    vector<int> arrayRankTransform(vector<int>& arr) {
        std::vector<int> b(arr.size());
        std::iota(b.begin(), b.end(), 0);
        std::sort(b.begin(), b.end(), [&](int i, int j) { return arr[i] < arr[j]; });
        int rank = 1;
        std::vector<int> ans(arr.size());
        for (int i = 0; i < b.size(); ++i) {
            if (i > 0 && arr[b[i]] != arr[b[i - 1]]) {
                ++rank;
            }
            ans[b[i]] = rank;
        }
        return ans;
    }
};