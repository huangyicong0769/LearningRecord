#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    long long maximumHappinessSum(vector<int>& happiness, int k) {
        sort(happiness.begin(), happiness.end(), std::greater<int>());
        long long ans = 0;
        for (int i = 0; i < k; i++)
            if (i >= happiness[i])
                break;
            else ans += happiness[i] - i;
        return ans;
    }
};