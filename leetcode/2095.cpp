#include "lc.hpp"

class Solution {
public:
    ListNode* deleteMiddle(ListNode* head) {
        ListNode *slow = head, *fast = head, *prev = nullptr;
        while (fast && fast->next) {
            prev = slow;
            slow = slow->next;
            fast = fast->next->next;
        }
        if (prev) {
            prev->next = slow->next;
        } else {
            head = head->next;
        }
        return head;
    }
};