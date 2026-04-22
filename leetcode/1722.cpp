#include "lc.hpp"

class Solution {
    std::vector<int> fa;

    int getfa(int x){
        if (fa[x] == x) 
            return x;
        else 
            return fa[x] = getfa(fa[x]);
    }

public:
    int minimumHammingDistance(vector<int>& source, vector<int>& target, vector<vector<int>>& allowedSwaps) {
        const int N = source.size();
        for (int i = 0; i < N; i++)
            fa.push_back(i);
        for (const auto &swp:allowedSwaps){
            const int &a = swp[0], &b = swp[1];
            fa[getfa(a)] = getfa(b);
        }
        std::unordered_map<int, std::unordered_map<int, int>> h;
        for (int i = 0; i < N; i++){
            h[getfa(i)][source[i]]++; // to make sure exitence
        }
        for (int i = 0; i < N; i++){
            h[getfa(i)][target[i]]--; // to make sure exitence
        }
        int ans = 0;
        for (const auto & [i, m] : h){
            for (const auto &[v, p]:m){
                ans += abs(p);
            }
        }
        return ans / 2;
    }
};