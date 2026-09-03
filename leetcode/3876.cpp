#include "lc.hpp"

class Solution {
public:
    bool uniformArray(vector<int>& nums1) {
        std::ranges::sort(nums1);
        int allodd = 0, alleven = 0;
        int preodd = 0;
        for (int i = 0; i < nums1.size(); i++){
            int canodd = (nums1[i] % 2) || (preodd > 0);
            int caneven = (nums1[i] % 2 == 0) || (preodd > 0);
            allodd += canodd && !caneven;
            alleven += caneven && !canodd;
            preodd += (nums1[i] % 2);
        }
        return allodd == 0 || alleven == 0;
    }
};