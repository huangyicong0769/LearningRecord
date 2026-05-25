#include "lc.hpp"

class Solution {
public:
    bool canReach(string s, int minJump, int maxJump) {
        const int N = s.size();
        std::vector<int> zeros;
        std::vector<char> f(N, 0);
        zeros.push_back(0);
        for (int i = 1; i < N; i++){
            if (s[i] == '1') continue;
            auto it = std::lower_bound(zeros.begin(), zeros.end(), std::max(0, i - maxJump));
            if (it == zeros.end() || *it > i - minJump) continue;
            zeros.push_back(i);
            f[i] = 1;
        }
        return f[N - 1] == 1;
    }
};

class Solution2 {
public:
    bool canReach(string s, int minJump, int maxJump) {
        const int N = s.size();
        std::queue<int> zeros;
        std::vector<char> f(N, 0);
        zeros.push(0);
        for (int i = 1; i < N; i++){
            if (s[i] == '1') continue;
            while (!zeros.empty() && zeros.front() < i - maxJump) zeros.pop();
            if (zeros.empty() || zeros.front() > i - minJump) continue;
            zeros.push(i);
            f[i] = 1;
        }
        return f[N - 1] == 1;
    }
};