#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    int maxDistinctElements(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int ans = 0;
        int r = -0x7FFFFFFF;
        for (int num : nums){
            if (num + k <= r)
                continue;
            if (r < num - k)
                r = num - k;
            else r++;
            ans++;
        }
        return ans;
    }
};