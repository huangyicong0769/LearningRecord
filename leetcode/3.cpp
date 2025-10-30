#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        bool bitset[128] = {0};
        int max_l = 0;

        if (s == "") return 0;

        bitset[s[0]] = 1;
        for (int i = 0, j = 0; i < s.size();){
            while (j + 1 < s.size() && !bitset[s[j+1]])
                bitset[s[++j]] = 1;
            if (j - i > max_l)
                max_l = j - i;
            if (j + 1 == s.size())
                break;
            while (i < j && s[i] != s[j+1]) 
                bitset[s[i++]] = 0;
            if (i < s.size())
                bitset[s[i++]] = 0;
        }
        return max_l + 1;
    }
};

int main(){
    Solution s;
    cout << s.lengthOfLongestSubstring("abcabcbb") << endl;
}