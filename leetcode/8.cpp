#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    int myAtoi(string s) {
        long long ans = 0;
        int neg = 1;
        int i = 0;
        while (i < s.size() && s[i] == ' ') i++;
        if (i < s.size() && (s[i] == '-' || s[i] == '+')){
            if (s[i] == '-') neg = -1;
            i++;
        }
        for (;i < s.size();i++){
            if (s[i] < '0' || s[i] > '9')
                break;
            ans *= 10;    
            ans += s[i] - '0';
            if (neg == 1 && ans > 0x7FFFFFFF)
                return 0x7FFFFFFF;
            if (neg == -1 && ans > 0x80000000U)
                return -2147483648;
        }
        return static_cast<int>(ans*neg);
    }
};

int main(){
    Solution s;
    string input;
    cin >> input;
    cout << s.myAtoi(input) << endl;
}