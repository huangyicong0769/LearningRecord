#include <iostream>
#include <string>
using namespace std;

class Solution {
public:
    bool isMatch(string s, string p) {
        bool f[22][22] = {0};
        f[0][0] = true;
        for (int j = 2; j <= p.size(); j++)
            f[0][j] |= (f[0][j-2] && p[j-1] == '*');
        for (int i = 1; i <= s.size(); i++){
            for (int j = 1; j <= p.size(); j++){
                f[i][j] |= (f[i-1][j-1] && (s[i-1] == p[j-1] || p[j-1] == '.'));
                if (p[j-1] == '*'){
                    f[i][j] |= ((f[i-1][j-1] || f[i-1][j] || f[i][j-1]) && (s[i-1] == p[j-2] || p[j-2]=='.'));
                    f[i][j] |= (f[i][j-2]);
                }
            }
        }
        for (int j = 0; j <= p.size(); j++){
            for (int i = 0; i <= s.size(); i++)
                cout << f[i][j] << ' ';
            cout << endl;
        }
        return f[s.size()][p.size()];
    }
};

int main(){
    string s, p;
    cin >> s >> p;
    Solution sol;
    cout << sol.isMatch(s, p) << endl;
}