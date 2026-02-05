#include "lc.hpp"

class Solution {
public:
    long long maxSumTrionic(vector<int>& nums) {
        const int N = nums.size();
        vector<char> state(N, 0);
        vector<pair<int, int>> dec;
        vector<long long> sum(N, 0);
        sum[0] = nums[0];
        for (int i = 1; i < N; i++){
            sum[i] = sum[i - 1] + nums[i];
            state[i] = nums[i - 1] > nums[i];
            if (nums[i - 1] > nums[i])
                state[i] = 1;
            else if (nums[i - 1] == nums[i])
                state[i] = 2;
            else 
                state[i] = 0;
            if (state[i - 1] != state[i]){
                if (state[i - 1] != 1)
                    dec.push_back({i - 1, -1});
                else dec.back().second = i - 1;
            }
        }
        // for (const auto & [p, q] : dec)
        //     cout << "(" << p << ", " << q << "), ";
        // cout << endl;
        long long ans = -LLONG_MAX;
        for (int i = 0; i < dec.size(); i++){
            const auto & [p, q] = dec[i];
            if (p == 0 || q == N - 1 || q == -1)
                continue;
            long long s1 = -LLONG_MAX / 4, s2 = -LLONG_MAX / 4;
            for (int l = p - 1; l >= (i > 0 ? dec[i - 1].second : 0); l--){
                s1 = max(s1, sum[p] - (l > 0 ? sum[l - 1] : 0));
                if (state[l] == 2)
                    break;
            }
            for (int r = q + 1; r <= (i + 1< dec.size() ? dec[i + 1].first : N - 1); r++){
                if (state[r] == 2)
                    break;
                s2 = max(s2, sum[r] - sum[q]);
            }
            ans = max(ans, s1 + s2 + sum[q] - sum[p]);
        }
        return ans;
    }
};