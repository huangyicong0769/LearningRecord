#include "lc.hpp"

class Solution {
public:
    vector<long long> distance(vector<int>& nums) {
        std::unordered_map<int, vector<int>> s;
        for (int i = 0; i < nums.size(); i++)
            s[nums[i]].push_back(i);
        vector<long long> arr(nums.size(), 0LL);
        for (auto &[_, v]:s){
            long long pre = 0LL, sur = std::accumulate(v.begin(), v.end(), 0LL);
            for (int i = 0; i < v.size(); i++){
                sur -= v[i];
                arr[v[i]] = sur - 1LL*(v.size() - 1 - i)*v[i] + 1LL*i*v[i] - pre;
                pre += v[i];
            }
        }
        return arr;
    }
};