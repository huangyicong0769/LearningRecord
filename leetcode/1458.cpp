#include <vector>
using namespace std;

class Solution {
public:
    int maxDotProduct(vector<int>& nums1, vector<int>& nums2) {
        int s[501];
        for (int j = 0; j <= nums2.size(); j++)
            s[j] = -0x7FFFFFFF;
        for (int i = 1; i <= nums1.size(); i++){
            int pre = -0x7FFFFFFF, diag = -0x7FFFFFFF;
            for (int j = 1; j <= nums2.size(); j++){
                int up = s[j];
                int p = nums1[i - 1]*nums2[j - 1];
                if (diag != -0x7FFFFFFF)
                    p = max(p, diag + nums1[i - 1]*nums2[j - 1]);
                int cur = max(up, max(pre, p));
                diag = up;
                pre = cur;
                s[j] = cur;
            }
        }
        return s[nums2.size()];
    }
};