#include "lc.hpp"

class Solution {
public:
    int rotatedDigits(int n) {
        auto C = [](const int& N, std::set<int>&& s){
            auto check = [&](int x) ->bool {
                while (x){
                    if (!s.contains(x % 10)) return false;
                    x /= 10;
                }
                return true;
            };
            int ret = 0;
            for (int i = 1; i <= N; i++){
                if (check(i)) 
                    ret++;
            }
            return ret;
        };
        return C(n, {0, 1, 2, 5, 6, 8, 9}) - C(n, {0, 1, 8});
    }
};

class Solution_dp {
    static constexpr int check[10] = {0,0,1,0,0,1,1,0,0,1};
public:
    int rotatedDigits(int n) {
        if (n == 10000) n--;
        vector<int> digits;
        while (n) {
            digits.push_back(n % 10);
            n /= 10;
        }
        reverse(digits.begin(), digits.end());

        std::vector mem(5, vector(2, vector(2, -1)));
        function<int(int, bool, bool)> dfs = [&](int pos, bool bound, bool diff) -> int {
            if (pos == digits.size())
                return diff;
            if (mem[pos][bound][diff] != -1)
                return mem[pos][bound][diff];
            int ret = 0;
            for (int i : {0, 1, 2, 5, 6, 8, 9}){
                if (bound && i > digits[pos]) 
                    break;
                ret += dfs(pos + 1, bound && i == digits[pos], diff || check[i]);
            }
            return mem[pos][bound][diff] = ret;
        };
        return dfs(0, true, false);
    }
};