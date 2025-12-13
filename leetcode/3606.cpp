#include <vector>
#include <string>
using namespace std;

class Solution {
    bool isValid(const string &s){
        if (s.empty()) 
            return false;
        for (const char & ch : s)
            if (!(ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z' || ch >= '0' && ch <= '9' || ch == '_'))
                return false;
        return true;
    }
public:
    vector<string> validateCoupons(vector<string>& code, vector<string>& businessLine, vector<bool>& isActive) {
        vector<int> index;
        for (int i = 0; i < code.size(); i++){
            if (isValid(code[i]) && (businessLine[i] == "electronics" || businessLine[i] == "grocery" || businessLine[i] == "pharmacy" || businessLine[i] == "restaurant") && isActive[i])
                index.push_back(i);
        }
        sort(index.begin(), index.end(), [&](const int &a, const int &b)->bool{
            return businessLine[a] < businessLine[b] || businessLine[a] == businessLine[b] && code[a] < code[b];
        });
        vector<string> ans;
        for (int & i : index)
            ans.push_back(std::move(code[i]));
        return std::move(ans);
    }
};
