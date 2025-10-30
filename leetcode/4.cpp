#include <iostream>
#include <vector>
using namespace std;

class Solution {
    const int INTMAX = 1e6 + 5;
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        const int &n = nums1.size(), &m = nums2.size();
        if (n > m)
            return findMedianSortedArrays(nums2, nums1);
        if (n == 0)
            return m%2 ? nums2[m/2] : double(nums2[m/2]+nums2[m/2-1])/2.0;
        int ans = 0;
        for (int l = -1, r = n; l <= r; ){
            int i = (l + r) / 2;
            int j = (n + m + 1) /2 - 2 - i;
            
            int a = getItem(i, nums1);
            int b = getItem(j + 1, nums2);
            cout << l << ' ' << r << ' ' << i << ' ' << j << ' ' << a << ' ' << b << endl;
            if (a <= b) {
                l = i + 1;
                ans = i;
            }
            else r = i - 1;
        }
        int i = ans;
        int j = (n + m + 1) /2 - 2 - i;
        int first = std::max(getItem(i, nums1), getItem(j, nums2));
        int second = std::min(getItem(i + 1, nums1), getItem(j + 1, nums2));
        if ((n+m)%2) return first;
        else return (double)(first + second) / 2.0;
    }
private:
    int getItem(int index, vector<int>& nums){
        if (index < 0) return -INTMAX;
        if (index >= nums.size()) return INT_MAX;
        return nums[index];
    }
};

int main(){
    int n, m;
    vector<int> nums1, nums2;
    cin >> n >> m;
    for (int i = 0; i < n; i++){
        int temp;
        cin >> temp;
        nums1.push_back(temp);
    }
    for (int i = 0; i < m; i++){
        int temp;
        cin >> temp;
        nums2.push_back(temp);
    }
    Solution sol;
    cout << sol.findMedianSortedArrays(nums1, nums2) << endl;
}