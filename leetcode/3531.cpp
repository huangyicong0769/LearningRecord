#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

class Solution {
public:
    int countCoveredBuildings(int n, vector<vector<int>>& buildings) {
        std::unordered_map<int, vector<int>> lines;
        for (auto & building : buildings)
            lines[building[1]].push_back(building[0]);
        for (auto & [y, line]:lines)
            sort(line.begin(), line.end());
        std::unordered_map<int, std::vector<int>::iterator> heads;
        std::map<int, std::vector<int>> m;
        for (auto & [y, line]:lines){
            heads[y] = line.begin();
            if (heads[y] != line.end())
                m[*heads[y]].push_back(y);
        }
        int ans = 0;
        while (!m.empty()){
            // cout << "!===" << endl;
            // for (auto & [x, v] : m){
            //     cout << x << ": ";
            //     for (auto & it : v) cout << it << ", ";
            //     cout << endl;
            // }
            auto & [x, v] = *m.begin();
            sort(v.begin(), v.end());
            for (int i = 1; i < v.size() - 1; i++)
                if (heads[v[i]] != lines[v[i]].begin() && std::next(heads[v[i]]) != lines[v[i]].end())
                    ans++;
            for (auto & y:v){
                if (std::next(heads[y]) != lines[y].end()){
                    heads[y] = std::next(heads[y]);
                    m[*heads[y]].push_back(y);
                }
            }
            m.erase(m.begin());
        }
        return ans;
    }
};

int main(){
    Solution sol;
    vector<vector<int>> v = {{1,2},{2,2},{3,2},{2,1},{2,3}};
    cout << sol.countCoveredBuildings(3, v) << endl;
}