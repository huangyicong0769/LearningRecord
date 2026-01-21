class Solution {
    int findAns(int x){
        for (int i = 0; i <= x; i++)
            if (i | (i + 1) == x)
                return i;
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