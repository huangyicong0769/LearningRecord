#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

class Solution {
public:
    long long maxRunTime(int n, vector<int>& batteries) {
        long long ans = 0;
        for (long long l = 0, r = std::accumulate(batteries.begin(), batteries.end(), 0LL); l <= r;){
            long long mid = (l + r) >> 1;
            if (verify(mid, n, batteries)){
                ans = mid;
                l = mid + 1;
            }else r = mid - 1;
        }
        return ans;
    }
    bool verify(long long &k, int &n, std::vector<int> &v) {
        long long sum = 0;
        for (auto &a : v){
            sum += min(k, static_cast<long long>(a));
            if (sum >= k*n) return true;
        }
        return false;
    }
};