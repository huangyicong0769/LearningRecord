#include <vector>
#include <queue>
#include <tuple>
#include <functional>
using namespace std;

class Solution_AI {
public:
    int minimumPairRemoval(vector<int>& nums) {
        int n = (int)nums.size();
        if (n <= 1) return 0;

        // Doubly linked list to track adjacency after merges.
        vector<long long> val(nums.begin(), nums.end());
        vector<int> prev(n), next(n), leftIdx(n);
        vector<char> alive(n, 1);
        for (int i = 0; i < n; ++i) {
            prev[i] = i - 1;
            next[i] = (i + 1 < n) ? i + 1 : -1;
            leftIdx[i] = i; // leftmost original index of this segment
        }

        auto is_bad = [&](int a, int b) -> bool {
            return a != -1 && b != -1 && val[a] > val[b];
        };

        int bad = 0;
        for (int i = 0; i + 1 < n; ++i) bad += is_bad(i, i + 1);
        if (bad == 0) return 0;

        // Min-heap of pairs (sum, leftIdx, leftNode).
        using State = tuple<long long, int, int>;
        priority_queue<State, vector<State>, greater<State>> pq;
        for (int i = 0; i + 1 < n; ++i) {
            pq.emplace(val[i] + val[i + 1], leftIdx[i], i);
        }

        auto remove_edge = [&](int a, int b) {
            if (a != -1 && b != -1 && alive[a] && alive[b] && next[a] == b && val[a] > val[b]) {
                --bad;
            }
        };

        auto add_edge = [&](int a, int b) {
            if (a != -1 && b != -1 && alive[a] && alive[b] && next[a] == b && val[a] > val[b]) {
                ++bad;
            }
        };

        int ops = 0;
        while (true) {
            // Fetch the valid minimal-sum leftmost pair.
            int u = -1, v = -1;
            while (!pq.empty()) {
                auto [s, lidx, left] = pq.top();
                v = (alive[left] ? next[left] : -1);
                if (alive[left] && v != -1 && alive[v] && next[left] == v && leftIdx[left] == lidx && val[left] + val[v] == s) {
                    u = left;
                    pq.pop();
                    break;
                }
                pq.pop(); // stale entry
            }
            if (u == -1) break; // should not happen

            ++ops;
            int bnode = next[u]; // right neighbor to merge

            int prevNode = prev[u];
            int nextNode = next[bnode];

            // Remove badness contributions of disappearing edges.
            remove_edge(prevNode, u);
            remove_edge(u, bnode);
            remove_edge(bnode, nextNode);

            // Merge u and bnode into u.
            val[u] = val[u] + val[bnode];
            leftIdx[u] = leftIdx[u]; // unchanged; leftmost index stays with left node
            alive[bnode] = 0;

            // Relink neighbors.
            if (prevNode != -1) next[prevNode] = u;
            prev[u] = prevNode;
            next[u] = nextNode;
            if (nextNode != -1) prev[nextNode] = u;

            // Add new edges' badness contributions.
            add_edge(prevNode, u);
            add_edge(u, nextNode);

            // Push new potential pairs to the heap.
            if (prevNode != -1) pq.emplace(val[prevNode] + val[u], leftIdx[prevNode], prevNode);
            if (nextNode != -1) pq.emplace(val[u] + val[nextNode], leftIdx[u], u);

            if (bad == 0) return ops;
        }

        return ops;
    }
};

class Solution {
public:
    int minimumPairRemoval(vector<int>& nums) {
        auto valid = [](const vector<int>& v) -> bool {
            for (int i = 1; i < v.size(); i++)
                if (v[i] < v[i - 1]) return false;
            return true;
        };

        int ans = 0;
        while (!valid(nums)){
            int k = 1;
            for (int i = 2; i < nums.size(); i++)
                if (nums[k - 1] + nums[k] > nums[i - 1] + nums[i])
                    k = i;
            vector<int> v;
            for (int i = 0; i < k; i++)
                v.push_back(nums[i]);
            v.back() += nums[k];
            for (int i = k + 1; i < nums.size(); i++)
                v.push_back(nums[i]);
            nums = std::move(v);
        }
        return ans;
    }
};