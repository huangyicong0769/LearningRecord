#include <vector>
#include <utility>
#include <queue>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        priority_queue<pair<int, int>> pq;
        ListNode* head = new ListNode();
        ListNode* tail = head;
        for (int i = 0; i < lists.size(); i++){
            if (lists[i] != nullptr){
                pq.push(make_pair(-1*(lists[i]->val), i));
                lists[i] = lists[i]->next;
            }
        }
        while (!pq.empty()){
            auto cur = pq.top();
            pq.pop();
            tail->next = new ListNode(-1*(cur.first));
            tail = tail->next;
            if (lists[cur.second]!=nullptr){
                pq.push(make_pair(-1*(lists[cur.second]->val), cur.second));
                lists[cur.second] = lists[cur.second]->next;
            }
        }
        return head->next;
    }
};