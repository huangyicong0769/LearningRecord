#include "lc.hpp"

class Solution {
public:
    int minJumps(vector<int>& arr) {
        std::unordered_map<int, std::vector<int>> js;
        for(int i = 0; i < arr.size(); i++){
            js[arr[i]].push_back(i);
        }
        std::unordered_map<int, bool> visj;
        std::vector<int> vis(arr.size(), 0);
        std::queue<int> q;
        q.push(0);
        vis[0] = 1;
        while (!q.empty()){
            int i = q.front();
            q.pop();
            if (i == arr.size() - 1){
                return vis[i] - 1;
            }
            if (i - 1 >= 0 && vis[i - 1] == 0){
                vis[i - 1] = vis[i] + 1;
                q.push(i - 1);
            }
            if (i + 1 < arr.size() && vis[i + 1] == 0){
                vis[i + 1] = vis[i] + 1;
                q.push(i + 1);
            }
            if (!visj[arr[i]]){
                visj[arr[i]] = true;
                for (const int &j : js[arr[i]])
                    if (!vis[j]){
                        vis[j] = vis[i] + 1;
                        q.push(j);
                    }
            }
        }
        return 0;
    }
};