#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    string longestPalindrome(string s) {
        string ss = "#";
        for (auto c : s){
            ss.push_back(c);
            ss.push_back('#');
        }
        s = ss;
        int l[2005]={0};
        int j = 0;
        for (int i = 0; i < s.size(); i++){
            if (j + l[j] > i)
                if (2 * j - i >= 0)
                    l[i] = min(l[2 * j - i], j + l[j] - i);
                else 
                    l[i] = j + l[j] - i;
            while (i - l[i] - 1 >= 0 && i + l[i] + 1 < s.size() && s[i + l[i] + 1] == s[i - l[i] - 1])
                l[i]++;
            if (i + l[i] > j + l[j])
                j = i;
        }

        int max_l = 0;
        for (int i = 0; i < s.size(); i++){
            if (l[i] > l[max_l])
                max_l = i;
        }

        string ans = "";
        for (int i = max_l - l[max_l]; i <= max_l + l[max_l]; i++)
            if (s[i] != '#')
                ans += s[i];
        return ans;
    }
};

int main(){
    Solution s;
    string input = "aacabdkacaa";
    // cin >> input;
    cout << s.longestPalindrome(input) << endl;
}