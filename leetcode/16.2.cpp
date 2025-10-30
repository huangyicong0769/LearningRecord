#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        // for (int num : nums) cout << num << ' '; cout << endl;
        int ans = 0, min_diff = 0x7FFFFFFF;
        for (int i = 0; i < nums.size(); i++){
            for (int j = i + 1, k = nums.size() - 1; j < k;){
                int tmp = nums[i] + nums[j] + nums[k];
                // cout << nums[i] << ' ' << nums[j] << ' ' << nums[k] << endl;
                if (min_diff > abs(target - tmp)){
                    ans = tmp;
                    min_diff = abs(target - tmp);
                }
                if (tmp == target) return tmp;
                if (tmp > target) k--;
                if (tmp < target) j++;
            }
        }
        return ans;
    }
};

int main(){
    int n, t;
    cin >> n >> t;
    vector<int> h;
    for (int i = 0; i < n; i++){
        int tmp;
        cin >> tmp;
        h.push_back(tmp);
    }
    Solution s;
    cout << s.threeSumClosest(h, t)<< endl;
}