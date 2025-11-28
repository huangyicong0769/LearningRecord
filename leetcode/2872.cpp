#include<vector>
using namespace std;

class Solution {
    vector<vector<int>> son;
    vector<int> v;
    int ans, n, k;

    void dfs(int x, int fa){
        for (auto &p:son[x]){
            if (p == fa) continue;
            dfs(p, x);
            v[x] += v[p];
            v[x] %= k;
        }
        if (v[x] % k == 0){
            // cout << x << " " << v[x] << endl;
            ans++;
            v[x] = 0;
        }
    }

public:
    int maxKDivisibleComponents(int n, vector<vector<int>>& edges, vector<int>& values, int k) {
        son.resize(n);
        ans = 0;
        this->n = n;
        this->k = k;
        this->v = std::move(values);
        for (auto &edge:edges){
            son[edge[0]].push_back(edge[1]);
            son[edge[1]].push_back(edge[0]);
        }
        dfs(0, -1);
        return ans;
    }
};