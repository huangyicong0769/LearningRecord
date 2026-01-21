#include <vector>
using std::vector;

class Solution {
    int findAns(int x){
        for (unsigned int i = 1<<31; i ; i >>= 1){
            if ((i & x) == i){
                unsigned int y = i ^ x;
                if ((y | (y + 1)) == x)
                    return y;
            }
        }
        return -1;
    }
public:
    vector<int> minBitwiseArray(vector<int>& nums) {
        vector<int> ans(nums.size());
        for (int i = 0; i < nums.size(); i++)
            ans[i] = findAns(nums[i]);
        return ans;
    }
};