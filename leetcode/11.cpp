#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int maxArea(vector<int>& height) {
        int ans = 0 ;
        for (int i = 0, j = height.size()-1; i < j; ){
            ans = max(ans, min(height[i], height[j]) * (j - i));
            // cout << i << ' ' << j << endl;
            if (height[i] > height[j])
                j--;
            else i++;
        }
        return ans;
    }
};

int main(){
    int n;
    cin >> n;
    vector<int> h;
    h.resize(n);
    for (auto& i : h)
        cin >> i;
    Solution s;
    cout << s.maxArea(h)<< endl;
}

