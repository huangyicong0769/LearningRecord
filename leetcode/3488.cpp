#include "lc.hpp"

class Solution {
public:
    vector<int> solveQueries(vector<int>& nums, vector<int>& queries) {
        const int N = nums.size();
        std::vector<int> pre(3 * N, -1), sur(3 * N, -1);
        std::unordered_map<int, int> index;
        for (int i = 0; i < 3 * N; i++){
            if (index.find(nums[i % N]) != index.end())
                pre[i] = index[nums[i % N]];
            index[nums[i % N]] = i;
        }
        index.clear();
        for (int i = 3 * N - 1; i >= 0; i--){
            if (index.find(nums[i % N]) != index.end())
                sur[i] = index[nums[i % N]];
            index[nums[i % N]] = i;
        }
        std::vector<int> ans;
        for (auto q:queries){
            q += N;
            int dist = -1;
            if (pre[q] == -1 && sur[q] != -1)
                dist = sur[q] - q;
            else if (pre[q] != -1 && sur[q] == -1)
                dist = q - pre[q];
            else if (pre[q] != -1 && sur[q] != -1) 
                dist = min(q - pre[q], sur[q] - q);
            ans.push_back(dist >= N ? -1 : dist);
        }
        return ans;
    }
};