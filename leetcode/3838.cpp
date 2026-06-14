#include "lc.hpp"

class Solution {
public:
    string mapWordWeights(vector<string>& words, vector<int>& weights) {
        auto val = [&](const string& s) {
            int sum = 0;
            for (char c : s)
                sum += weights[c - 'a'];
            return sum;
        };
        string ans;
        for (const string& w : words) 
            ans.push_back('z' - (val(w) % 26));
        return ans;
    }
};