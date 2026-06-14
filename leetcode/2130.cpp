#include "lc.hpp"

class Solution {
public:
    int pairSum(ListNode* head) {
        std::vector<int> v;
        for (; head != nullptr; head = head->next)
            v.push_back(head->val);
        int ans = 0;
        for (int i = 0; i < v.size()/2; i++)
            ans = std::max(ans, v[i] + v[v.size() - 1 - i]);
        return ans;
    }
};