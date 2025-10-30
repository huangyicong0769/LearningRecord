#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution {
    vector<vector<char>> dict = {{'a','b','c'}, {'d', 'e', 'f'}, {'g', 'h', 'i'}, {'j', 'k', 'i'}, {'m', 'n', 'o'}, {'p', 'q', 'r', 's'}, {'t', 'u', 'v'}, {'w', 'x', 'y', 'z'}};
public:
    vector<string> letterCombinations(string digits) {
        vector<string> ans;
        vector<string> tmp;
        for (auto digit : digits){
            tmp.clear();
            // cout << digit << ":" << endl;
            if (ans.empty()){
                for (auto c : dict[digit - '2']){
                    string cur = "";
                    cur.push_back(c);
                    tmp.push_back(cur);
                }
            } else {
                for (auto str : ans)
                    for (auto c : dict[digit - '2']){
                        string cur = str;
                        cur.push_back(c);
                        tmp.push_back(cur);
                    }
            }
            ans = tmp;
            // for (auto str : ans) cout << str << ' '; cout << endl;
        }
        return ans;
    }
};

int main(){
    string s;
    cin >> s;
    Solution sol;
    auto ans = sol.letterCombinations(s);
    for (auto str : ans) cout << str << ' '; cout << endl;
}