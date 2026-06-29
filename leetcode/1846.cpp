#include "lc.hpp"

class Solution {
public:
    int maximumElementAfterDecrementingAndRearranging(vector<int>& arr) {
        std::sort(arr.begin(), arr.end());
        for (int i = 0; i < arr.size(); i++){
            if (arr[i] > i + 1)
                arr[i] = i + 1;
            if (i > 0 && arr[i] > arr[i - 1] + 1)
                arr[i] = arr[i - 1] + 1;
        }
        return arr.back();
    }
};