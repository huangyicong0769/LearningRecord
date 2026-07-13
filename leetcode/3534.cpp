#include "lc.hpp"

class Solution {
public:
    vector<int> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
        const int M = std::ranges::max(nums);

        std::vector<char> exists(M + 1, false);
        for (int x : nums)
            exists[x] = true;

        std::vector<int> f(M + 1, -1);
        f[0] = exists[0] ? 0 : -1;
        for (int x = 1; x <= M; x++)
            f[x] = exists[x] ? x : f[x - 1];

        std::vector<int> comp(M + 1, -1);
        int componentId = -1;
        int previousValue = -1;
        for (int x = 0; x <= M; x++) {
            if (!exists[x]) {
                continue;
            }

            if (previousValue == -1 ||
                x - previousValue > maxDiff) {
                ++componentId;
            }

            comp[x] = componentId;
            previousValue = x;
        }

        int LOG = 1;
        while ((1 << LOG) <= n) {
            ++LOG;
        }

        std::vector nxt(LOG, std::vector<int>(M + 1));
        for (int x = 0; x <= M; x++) {
            int right = std::min(M, x + maxDiff);
            int destination = f[right];
            nxt[0][x] = destination == -1 ? x : destination;
        }
        for (int k = 1; k < LOG; k++) {
            for (int x = 0; x <= M; x++) {
                nxt[k][x] = nxt[k - 1][nxt[k - 1][x]];
            }
        }

        std::vector<int> ans;
        ans.reserve(queries.size());
        for (const auto& q : queries) {
            int a = q[0], b = q[1];
            if (a == b) {
                ans.push_back(0);
                continue;
            }

            int u = nums[a], v = nums[b];
            if (u == v) {
                ans.push_back(1);
                continue;
            }

            if (u > v)
                std::swap(u, v);

            if (comp[u] != comp[v]) {
                ans.push_back(-1);
                continue;
            }

            int cnt = 0;
            for (int k = LOG - 1; k >= 0; k--)
                if (nxt[k][u] < v) {
                    u = nxt[k][u];
                    cnt += 1 << k;
                }
            ans.push_back(cnt + 1);
        }

        return ans;
    }
};

class Solution {
    static constexpr int LOG = 17;

public:
    vector<int> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
        const int M = std::ranges::max(nums);
        std::vector<int> id(M + 1, -1);
        for (int x : nums)
            id[x] = 0;

        std::vector<int> values;
        values.reserve(n);
        for (int x = 0; x <= M; ++x)
            if (id[x] != -1) {
                id[x] = values.size();
                values.push_back(x);
            }

        const int K = values.size();
        std::vector<int> componentEnd(K);
        componentEnd[K - 1] = K - 1;
        for (int i = K - 2; i >= 0; --i)
            if (values[i + 1] - values[i] <= maxDiff)
                componentEnd[i] = componentEnd[i + 1];
            else
                componentEnd[i] = i;

        std::vector<std::array<int, LOG>> jump(K);

        int right = 0;
        for (int left = 0; left < K; ++left) {
            if (right < left)
                right = left;
            while (right + 1 < K && values[right + 1] - values[left] <= maxDiff)
                ++right;
            jump[left][0] = right;
        }

        for (int k = 1; k < LOG; ++k) {
            for (int i = 0; i < K; ++i) {
                jump[i][k] = jump[jump[i][k - 1]][k - 1];
            }
        }

        std::vector<int> answer(queries.size());
        for (int qi = 0; qi < static_cast<int>(queries.size()); ++qi) {
            const int a = queries[qi][0];
            const int b = queries[qi][1];

            if (a == b) {
                answer[qi] = 0;
                continue;
            }

            int u = id[nums[a]];
            int v = id[nums[b]];

            if (u == v) {
                answer[qi] = 1;
                continue;
            }

            if (u > v) {
                std::swap(u, v);
            }

            if (v > componentEnd[u]) {
                answer[qi] = -1;
                continue;
            }

            if (jump[u][0] >= v) {
                answer[qi] = 1;
                continue;
            }

            int steps = 0;
            for (int k = LOG - 1; k >= 0; --k) {
                const int next = jump[u][k];

                if (next < v) {
                    u = next;
                    steps += 1 << k;
                }
            }
            answer[qi] = steps + 1;
        }
        return answer;
    }
};