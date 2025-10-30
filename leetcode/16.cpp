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
            for (int j = i + 2; j < nums.size(); j++){
                int goal = target - nums[i] - nums[j];
                int k = find(nums, i + 1, j - 1, goal);
                // cout << nums[i] << ' ' << nums[j] << ' ' << k << endl;
                if (min_diff > abs(goal - k)){
                    ans = nums[i] + nums[j] + k;
                    min_diff = abs(goal - k);
                }
            }
        }
        return ans;
    }
private:
    int find(vector<int>& nums, int begin, int end, int goal){
        // cout << ' ' << begin << ' ' << end << ' ' << goal << endl;
        int l = begin;
        int r = end;
        int mid = (l + r) / 2;
        while (l < r) {
            mid = (l + r) / 2;
            if (nums[mid] == goal)
                return nums[mid];
            if (nums[mid] > goal)
                r = mid-1;
            if (nums[mid] < goal)
                l = mid+1;
        }
        if (mid > begin && abs(goal - nums[mid]) > abs(goal - nums[mid - 1]))
            mid--;
        if (mid < end && abs(goal - nums[mid]) > abs(goal - nums[mid + 1]))
            mid++;
        return nums[mid];
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