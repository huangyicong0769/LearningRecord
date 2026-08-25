#include "lc.hpp"

class Solution {
public:
    int missingMultiple(vector<int>& nums, int k) {
        std::unordered_set<int> s;
        for (int a:nums){
            if (a%k==0) s.insert(a/k);
        }
        for (int i = 1; ; i++)
            if (!s.count(i)) return i*k;
        return k;
    }
};