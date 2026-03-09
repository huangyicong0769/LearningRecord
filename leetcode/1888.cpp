#include "lc.hpp"

class Solution {
public:
    int minFlips(string s) {
        const int N = s.size();
        int st[2]={0};
        for (int i = 0; i < N; i++)
            st[(i % 2) ^ (s[i] - '0')]++;
        int ans = min(st[0], st[1]);
        for (int i = 1; i < N; i++){
            // cout << "0: " << st[0] << ", " << st[1] << endl;
            st[0 ^ (s[i - 1] - '0')]--;
            // cout << "1: " << st[0] << ", " << st[1] << endl;
            swap(st[0], st[1]);
            // cout << "2: " << st[0] << ", " << st[1] << endl;
            st[((N - 1) % 2) ^ (s[i - 1] - '0')]++;
            ans = min(ans, min(st[0], st[1]));
            // cout << "3: " << st[0] << ", " << st[1] << endl << endl;
        }
        return ans;
    }
};