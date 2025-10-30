#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    string convert(string s, int numRows) {
        string tmp[numRows];
        int di = (numRows == 1 ? 0 : -1);
        for (int i = 0, j = 0; i < s.size(); i++, j+=di){
            tmp[j] += s[i];
            if (j == 0 || j == numRows - 1)
                di *= -1;
        }
        string ans = "";
        for (auto ss : tmp)
            ans += ss;
        return ans;
    }
};

int main(){
    Solution s;
    string input;
    int n;
    cin >> input >> n;
    cout << s.convert(input, n) << endl;
}