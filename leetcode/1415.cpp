#include "lc.hpp"

class Solution {
    char dict[3][2] = {{'b', 'c'}, {'a', 'c'}, {'a', 'b'}};
public:
    string getHappyString(int n, int k) {
        k--;
        string ans = "";
        int nums = 1 << (n - 1);
        if (k / nums > 2)
            return  "";
        ans += static_cast<char>(k / nums + 'a');
        k %= nums;
        for (int i = 2; i <= n; i++){
            nums >>= 1;
            if (k / nums > 1)
                return "";
            ans.push_back(dict[ans.back() - 'a'][k / nums]);
            k %= nums;
        }
        return ans;
    }
};