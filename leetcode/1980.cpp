#include <lc.hpp>

class Solution {
    int n;
    int b2i(string &x){
        int y = 0;
        for (char c : x){
            y <<= 1;
            y += c - '0';
        }
        return y;
    }
    string i2b(int x){
        string y = "";
        for (int i = 0; i < n; i++){
            y += static_cast<char>(x % 2 + '0');
            x >>= 1;
        }
        reverse(y.begin(), y.end());
        return y;
    }
public:
    string findDifferentBinaryString(vector<string>& nums) {
        unordered_set<int> s;
        n = nums.size();
        for (auto &num : nums)
            s.insert(b2i(num));
        for (int i = 0; i < (1 << n); i++) {
            if (s.find(i) == s.end())
                return i2b(i);
        }
        return "";
    }
};