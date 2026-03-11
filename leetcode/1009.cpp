// same to lc 476
#include "lc.hpp"

class Solution {
public:
    int b2i(const string &x){
        int y = 0;
        for (char c : x){
            y <<= 1;
            y += c - '0';
        }
        return y;
    }
    string i2b(int x){
        if (x == 0) return "0";
        string y = "";
        for (; x; x >>= 1){
            y += static_cast<char>(x % 2 + '0');
        }
        reverse(y.begin(), y.end());
        return y;
    }
    string cpl(const string &x){
        string y = x;
        for (char &ch : y){
            ch = (ch == '0' ? '1' : '0');
        }
        return y;
    }
    int bitwiseComplement(int n) {
        return b2i(cpl(i2b(n)));
    }
};