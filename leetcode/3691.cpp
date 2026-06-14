#include "lc.hpp"

class Solution {
    template <class __comp>
    struct MonoSum {
        std::deque<std::pair<int, int>> q;
        __comp comp;
        long long sum = 0;

        MonoSum(__comp comp = __comp{}) : comp(comp) {}

        void push(int v){
            int cnt = 1;
            while (!q.empty() && comp(v, q.back().first)){
                sum -= 1LL * q.back().first * q.back().second;
                cnt += q.back().second;
                q.pop_back();
            }
            q.push_back({v, cnt});
            sum += 1LL * v * cnt;
        }

        void pop(){
            q.front().second--;
            sum -= q.front().first;
            if (q.front().second == 0)
                q.pop_front();
        }
    };

public:
    long long maxTotalValue(vector<int>& nums, int k) {
        const int N = nums.size();

        auto check = [&](long long x) -> long long {
            long long bad = 0;
            deque<int> maxq, minq;

            for (int l = 0, r = 0; r < N; r++) {
                while (!maxq.empty() && nums[maxq.back()] <= nums[r])
                    maxq.pop_back();
                maxq.push_back(r);

                while (!minq.empty() && nums[minq.back()] >= nums[r])
                    minq.pop_back();
                minq.push_back(r);

                while (!maxq.empty() &&
                    1LL * nums[maxq.front()] - nums[minq.front()] >= x) {
                    if (maxq.front() == l) maxq.pop_front();
                    if (minq.front() == l) minq.pop_front();
                    l++;
                }

                bad += r - l + 1; // value < x 的数量
            }

            long long total = 1LL * N * (N + 1) / 2;
            return total - bad; // value >= x 的数量
        };

        auto cal = [&](long long x) -> std::pair<long long, long long> {
            long long sum = 0;
            long long cnt = 0;
            MonoSum<std::greater_equal<>> allmax, midmax;
            MonoSum<std::less_equal<>> allmin, midmin;
            for (int l = 0, r = 0; r < N; r++){
                allmax.push(nums[r]);
                allmin.push(nums[r]);
                midmax.push(nums[r]);
                midmin.push(nums[r]);
                while (!midmax.q.empty() && midmax.q.front().first - midmin.q.front().first >= x) {
                    midmax.pop();
                    midmin.pop();
                    l++;
                }
                sum += allmax.sum - allmin.sum - midmax.sum + midmin.sum;
                cnt += l;
            }
            
            return {sum, cnt};
        };

        int t = 0;
        for (int l = 0, r = std::min((int)1e9, (int)std::ranges::max(nums)); l <= r;){
            int mid = (l + r) / 2;
            long long cnt = check(mid);
            if (cnt >= k){
                t = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        auto [sum, cnt] = cal(t);
        return sum - (cnt - k) * t;
    }
};