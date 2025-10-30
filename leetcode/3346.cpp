#include <vector>
using namespace std;

class Solution {
public:
    int maxn;
    int maxFrequency(vector<int>& nums, int k, int numOperations) {
        int fs[100001] = {0};
        maxn = -1;
        for (int& num : nums){
            fs[num]++;
            maxn = max(maxn, num);
        }
        for (int i = 1; i <= maxn; i++)
            fs[i] += fs[i - 1];
        int ans = 0;
        for (int i = 1; i <= maxn; i++){
            ans = max(ans, min(numOperations + fs[i] - fs[i-1], fs[indexReg(i+k)] - fs[indexReg(i-k-1)]));
        }
        return ans;
    }
    int indexReg(const int& k){
        return std::max(0, std::min(maxn, k));
    }
};