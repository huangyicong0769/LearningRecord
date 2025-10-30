#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        long long tg = target;
        sort(nums.begin(), nums.end());
        // for (auto i : nums) cout << i << ' '; cout <<endl;
        vector<vector<int>> ans;
        for (int i = 0; i < nums.size(); i++){
            if (i > 0 && nums[i] == nums[i - 1])
                continue;
            for (int j = i + 1; j < nums.size(); j++){
                if (j > i + 1 && nums[j] == nums[j - 1])
                    continue;
                for (int k1 = j + 1, k2 = nums.size() - 1; k1 < k2;){
                    // cout << i << ' ' << j << ' ' << k1 << ' ' << k2 << endl;
                    long long tmp = (long long)nums[i] + (long long)nums[j] + (long long)nums[k1] + (long long)nums[k2];
                    if (tmp == tg){
                        ans.push_back({nums[i], nums[j], nums[k1], nums[k2]});
                    }
                    if (tg >= tmp){
                        do{
                            k1++;
                        }while(k1 < k2 && nums[k1] == nums[k1 - 1]);
                    }else if (tg < tmp){
                        do{
                            k2--;
                        }while(k1 < k2 && nums[k2] == nums[k2 + 1]);
                    }
                }
            }
        }
        return ans;
    }
};

int main(){
    Solution sol;
    vector<int> input = {-2,-1,-1,1,1,2,2};
    auto ans = sol.fourSum(input, 0);
    for (auto v : ans){
        for (auto i : v) cout << i << ' '; cout <<endl;
    }
}