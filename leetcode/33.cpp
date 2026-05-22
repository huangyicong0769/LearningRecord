#include "lc.hpp"

class Solution {
public:
    int search(vector<int>& nums, int target) {
        for (int l = 0, r = nums.size() - 1; l <= r; ){
            int mid = (l + r) / 2;
            if (nums[mid] == target)
                return mid;
            if (nums[l] == nums[mid])
                l++;
            else if (nums[mid] == nums[r])
                r--;
            else if (nums[l] > nums[mid] && nums[mid] < nums[r]){
                if (target < nums[mid])
                    r = mid - 1;
                else{
                    if (target >= nums[l])
                        r = mid - 1;
                    else 
                        l = mid + 1;
                }
            }else if (nums[l] < nums[mid] && nums[mid] > nums[r]){
                if (target > nums[mid])
                    l = mid + 1;
                else{
                    if (target >= nums[l])
                        r = mid - 1;
                    else 
                        l = mid + 1;
                }
            }else {
                if (target < nums[mid])
                    r = mid - 1;
                else 
                    l = mid + 1;
            }
        }
        return -1;
    }
};