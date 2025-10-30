#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    vector<string> generateParenthesis(int n) {
        this->n = n;
        vector<string> ans;
        dfs(ans, "", 0);
        return ans;
    }
private:
    int n;
    void dfs(vector<string> &ans, string s, int state){
        if (s.size() == 2 * n){
            ans.push_back(s);
            return;
        }
        if (state < (2*n - s.size())){
            dfs(ans, s + '(', state + 1);
        }
        if (state){
            dfs(ans, s + ')', state - 1);
        }
    }
};

int main(){
    int n;
    cin >> n;
    Solution sol;
    auto v = sol.generateParenthesis(n);
    for (auto i : v)
        cout << i << endl;
}