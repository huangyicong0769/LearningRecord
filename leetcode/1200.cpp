#include <vector>
#include <algorithm>
using std::vector;

class Solution {
public:
    vector<vector<int>> minimumAbsDifference(vector<int>& arr) {
        sort(arr.begin(), arr.end());
        vector<vector<int>> ans;
        for (int i = 1; i < arr.size(); i++){
            if (ans.empty() || ans[0][1] - ans[0][0] > arr[i] - arr[i - 1]){
                ans.clear();
                ans.push_back({arr[i - 1], arr[i]});
            }else if (!ans.empty() && ans[0][1] - ans[0][0] == arr[i] - arr[i - 1]){
                ans.push_back({arr[i - 1], arr[i]});
            }
        }    
        return ans;  
    }
};