#include "lc.hpp"

class Solution {
public:
    long long minimumCost(string source, string target, vector<char>& original, vector<char>& changed, vector<int>& cost) {
        const long long INF = LLONG_MAX;
        long long f[26][26] = {0};
        for (int i = 0; i < 26; i++)
            for (int j = 0; j < 26; j++)
                if (i != j) 
                    f[i][j] = INF;
        for (int i = 0; i < original.size(); i++)
            f[original[i] - 'a'][changed[i] - 'a'] = min(f[original[i] - 'a'][changed[i] - 'a'], static_cast<long long>(cost[i]));
        for (int k = 0; k < 26; k++)
            for (int i = 0; i < 26; i++)
                for (int j = 0; j < 26; j++)
                    f[i][j] = min(f[i][j], f[i][k] == INF || f[k][j] == INF ? INF : f[i][k] + f[k][j]);
        long long ans = 0;
        for (int i = 0; i < source.size(); i++){
            if (f[source[i] - 'a'][target[i] - 'a'] == INF)
                return -1;
            ans += f[source[i] - 'a'][target[i] - 'a'];
        }
        return ans;
    }
};