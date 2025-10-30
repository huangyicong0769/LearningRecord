#include <iostream>

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        ListNode *ret = new ListNode(0, head);
        int delay = 0, lap = 0;
        for (ListNode *f = ret, *b = ret; f != nullptr; f = f->next){
            std::cout << f->val << ' ' << delay << ' ' << lap << std::endl;
            if (delay < 2){
                delay++;
            }else{
                if (lap == 0){
                    b->next->next = f->next;
                    f->next = b->next;
                    b->next = f;
                    f = f->next;
                    lap = 2;
                }
                lap--;
                b = b->next;
            }
        }
        return ret->next;
    }
};

int main(){
    int n;
    std::cin >> n;
    ListNode *head = new ListNode();
    ListNode *tail = head;
    for (int i = 0; i < n; i++){
        int tmp;
        std::cin >> tmp;
        tail->next = new ListNode(tmp);
        tail = tail->next;
    }
    Solution sol;
    head = sol.swapPairs(head->next);
    for (ListNode* tail = head; tail != nullptr; tail=tail->next)
        std::cout << tail->val << ' ';
    std::cout << std::endl;
}