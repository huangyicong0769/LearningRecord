#include "lc.hpp"

class Solution {
public:
    vector<string> twoEditWords(vector<string>& queries, vector<string>& dictionary) {
        std::vector<std::string> ans;
        auto check = [&](const string &x)->bool {
            for (const auto &y:dictionary){
                int cnt = 0;
                for (int i = 0; i < x.size(); i++){
                    if (x[i] == y[i]) continue;
                    if (++cnt > 2)
                        break;
                }
                if (cnt <= 2)
                    return true;
            }
            return false;
        };
        for (const auto &word:queries){
            if (check(word))
                ans.push_back(word);
        }
        return ans;
    }
};