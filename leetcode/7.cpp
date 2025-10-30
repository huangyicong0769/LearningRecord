#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    int reverse(int x) {
        int neg = 1;

        if (x <= -2147483648)
            return 0;
        if (x < 0){
            x *= -1;
            neg = -1;
        }

        int y = 0;
        for (;x;){
            // cout << x << " " << y << endl;
            if (y > 0xCCCCCCC || y == 0xCCCCCCC && x > 7)
                return 0;
            y *= 10;
            y += x%10;
            x /= 10;
        }

        return y*neg;
    }
};

int main(){
    Solution s;
    int input;
    cin >> input;
    cout << s.reverse(input) << endl;
}