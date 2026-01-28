#include "lc.hpp"

class Solution {
public:
    int minCost(vector<vector<int>>& grid, int K) {
        const int N = static_cast<int>(grid.size());
        const int M = static_cast<int>(grid[0].size());
        const int INF = 100000000;

        vector<int> values;
        values.reserve(N * M);
        for (const auto& line : grid)
            for (int val : line)
                values.push_back(val);
        sort(values.begin(), values.end());
        values.erase(unique(values.begin(), values.end()), values.end());

        unordered_map<int, int> idx;
        idx.reserve(values.size() * 2);
        idx.max_load_factor(0.7f);
        for (int i = 0; i < values.size(); ++i)
            idx[values[i]] = i;

        vector<vector<int>> rank(N, vector<int>(M));
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < M; ++j)
                rank[i][j] = idx[grid[i][j]];

        vector<int> v(values.size(), INF);
        vector<int> next_v(values.size(), INF);
        vector<int> prevRow(M, INF);
        vector<int> curRow(M, INF);

        int ans = INT_MAX;
        for (int k = 0; k <= K; ++k) {
            // fill(next_v.begin(), next_v.end(), INF);
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < M; ++j) {
                    if (i == 0 && j == 0) {
                        curRow[j] = 0;
                    } else {
                        curRow[j] = INF;
                        if (i > 0) curRow[j] = min(curRow[j], prevRow[j]);
                        if (j > 0) curRow[j] = min(curRow[j], curRow[j - 1]);
                        if (curRow[j] < INF) curRow[j] += grid[i][j];
                        if (k > 0) curRow[j] = min(curRow[j], v[rank[i][j]]);
                    }
                    next_v[rank[i][j]] = min(next_v[rank[i][j]], curRow[j]);
                }
                prevRow.swap(curRow);
            }

            ans = min(ans, prevRow[M - 1]);

            for (int i = next_v.size() - 2; i >= 0; --i)
                next_v[i] = min(next_v[i], next_v[i + 1]);
            v.swap(next_v);
        }
        // auto print = [&](const vector<vector<vector<int>>>& a, int k){
        //     for (int i = 0; i <= N; i++){
        //         for (int j = 0; j <= M; j++)
        //             cout << a[i][j][k] << " ";
        //         cout << endl;
        //     }
        // };
        // for (int k = 0; k <= K; k++){
        //     cout << "k = " << k << endl;
        //     print(f, k);
        //     cout << endl;
        // }
        return ans;
    }
};