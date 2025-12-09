#include <vector>
#include <map>
using namespace std;

class Solution {
    const int M = 1e9 + 7;
public:
    int specialTriplets(vector<int>& nums) {
        std::unordered_map<int, vector<int>> m;
        for (int i = 0; i < nums.size(); i++)
            m[nums[i]].push_back(i);
        int ans = 0;
        for (int i = 1; i < nums.size() - 1; i++){
            auto &v = m[nums[i] * 2];
            auto t = std::upper_bound(v.begin(), v.end(), i);
            if (t == v.end()) continue;
            int r = v.end() - t;
            while (*t >= i && t != v.begin())
                t--;
            if (*t < i){
                int l = t - v.begin() + 1;
                ans = (ans + (1LL*l*r) % M) % M;
            }
        }
        return ans;
    }
};