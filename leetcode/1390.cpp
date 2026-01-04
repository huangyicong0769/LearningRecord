#include <vector>
#include <map>
#include <cmath>
#include <numeric>
using namespace std;

class Solution {
    std::unordered_map<int, int> factors;
    int factorize(int x){
        if (factors.find(x) != factors.end()) return factors[x];
        auto &v = factors[x];
        int cnt = 0;
        for (int i = 1; i <= sqrt(x); i++){
            if (x/i*i != x) continue;
            if (i != x/i){
                v += x/i;
                cnt++;
            }
            v += i;
            cnt++;
            if (cnt > 4) return factors[x] = 0;
        }
        if (cnt < 4) factors[x] = 0;
        return factors[x];
    }
public:
    int sumFourDivisors(vector<int>& nums) {
        int ans = 0;
        for (const auto &num:nums){
            auto v = factorize(num);
            ans += v;
        }
        return ans;
    }
};