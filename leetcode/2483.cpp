#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    int bestClosingTime(string &customers){
        const int &N = customers.size();
        int y = 0;
        for (const auto &c:customers)
            y += (c == 'Y');
        int n = (customers[0] == 'N');
        int cnt = y, ans = 0;
        for (int i = 1; i < N; i++){
            y -= (customers[i - 1] == 'Y');
            if (cnt > n + y){
                cnt = n + y;
                ans = i;
            }
            n += (customers[i] == 'N');
        }
        if (cnt > n) ans = N;
        return ans;
    }
};