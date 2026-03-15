#include "lc.hpp"

class Solution {
public:
    long long minNumberOfSeconds(int mountainHeight, vector<int>& workerTimes) {
        vector<int> assignTimes(workerTimes.size(), 0);
        
        auto qsum = [&](const auto x) -> long long {
            return 1LL * x * (x + 1) / 2;
        };

        auto cost = [&](const int x) -> long long {
            return qsum(assignTimes[x] + 1) * workerTimes[x];
        };

        auto cmp = [&](const int a, const int b) {    
            return cost(a) > cost(b);
        };

        priority_queue<int, vector<int>, decltype(cmp)> heap(cmp);

        for (int i = 0; i < workerTimes.size(); i++)
            heap.push(i);

        int accH = 0;
        long long ans = 0;
        while (accH < mountainHeight){
            int x = heap.top();
            heap.pop();
            ans = max(ans, cost(x));
            accH++;
            assignTimes[x]++;
            heap.push(x);
        }

        return ans;
    }
};

class SolutionOptimized {
public:
    long long minNumberOfSeconds(int mountainHeight, vector<int>& workerTimes) {
        auto canFinish = [&](long long limit) -> bool {
            long long removed = 0;

            for (int workerTime : workerTimes) {
                long double delta = 1.0L + 8.0L * (long double)limit / workerTime;
                long long cnt = (long long)((sqrtl(delta) - 1.0L) / 2.0L);

                while ((__int128)workerTime * cnt * (cnt + 1) / 2 > limit)
                    --cnt;
                while ((__int128)workerTime * (cnt + 1) * (cnt + 2) / 2 <= limit)
                    ++cnt;

                removed += cnt;
                if (removed >= mountainHeight)
                    return true;
            }

            return false;
        };

        int minWorkerTime = *min_element(workerTimes.begin(), workerTimes.end());
        long long left = 0;
        long long right = 1LL * minWorkerTime * mountainHeight * (mountainHeight + 1) / 2;

        while (left < right) {
            long long mid = left + (right - left) / 2;
            if (canFinish(mid))
                right = mid;
            else
                left = mid + 1;
        }

        return left;
    }
};

class SolutionHeapOptimized {
public:
    long long minNumberOfSeconds(int mountainHeight, vector<int>& workerTimes) {
        struct Node {
            long long nextCost;
            long long delta;
            int workerTime;
        };

        struct Compare {
            bool operator()(const Node& a, const Node& b) const {
                return a.nextCost > b.nextCost;
            }
        };

        priority_queue<Node, vector<Node>, Compare> heap;
        for (int workerTime : workerTimes)
            heap.push({workerTime, 2LL * workerTime, workerTime});

        long long ans = 0;
        while (mountainHeight--) {
            Node current = heap.top();
            heap.pop();

            ans = current.nextCost;
            current.nextCost += current.delta;
            current.delta += current.workerTime;

            heap.push(current);
        }

        return ans;
    }
};