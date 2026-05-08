#include "lc.hpp"

class Solution {
public:
    int minJumps(vector<int>& nums) {
        const int M = 1e6 + 1;
        std::vector<unsigned char> vis(M, 0);
        std::vector<int> p;

        for (int i = 2; i < M; i++){
            if (!vis[i]) p.push_back(i);
            for (auto pp: p){
                if (i * pp >= M)
                    break;
                vis[i * pp] = 1;
                if (i % pp == 0)
                    break;
            }
        }

        std::unordered_map<int, std::vector<int>> h;
        for (int i = 0; i < nums.size(); i++){
            for (auto pp : p){
                if (pp > nums[i])
                    break;
                if (nums[i] % pp == 0)
                    h[pp].push_back(i);
            }
        }

        std::queue<pair<int, int>> q;
        std::vector<unsigned char> vis2(nums.size(), 0);
        std::unordered_set<int> vis3;
        q.push({0, 0});
        vis2[0] = 1;
        while (!q.empty()){
            auto [i, step] = q.front();
            q.pop();
            if (i == nums.size() - 1)
                return step;
            if (!vis[nums[i]] && !vis3.count(nums[i])){
                for (auto j : h[nums[i]]){
                    if (!vis2[j]){
                        vis2[j] = 1;
                        q.push({j, step + 1});
                    }
                }
                vis3.insert(nums[i]);
            }
            if (i + 1 < nums.size() && !vis2[i + 1]){
                vis2[i + 1] = 1;
                q.push({i + 1, step + 1});
            }
             if (i - 1 >= 0 && !vis2[i - 1]){
                vis2[i - 1] = 1;
                q.push({i - 1, step + 1});
             }
        }
        return -1;
    }
};