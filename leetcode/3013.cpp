#include "lc.hpp"

class KHeap{
    size_t K;
    long long S;
    multiset<int> low;
    multiset<int> high;

    void move_low_max_to_high(){
        auto it = prev(low.end());
        S -= *it;
        high.insert(*it);
        low.erase(it);
    }

    void move_high_min_to_low(){
        auto it = high.begin();
        S += *it;
        low.insert(*it);
        high.erase(it);
    }

public:
    KHeap(int k = 0):K(k), S(0LL){}

    long long top(){
        return S;
    }

    void push(int num){
        if (low.size() < K){
            low.insert(num);
            S += num;
            return;
        }
        auto it = prev(low.end());
        if (num <= *it){
            low.insert(num);
            S += num;
            move_low_max_to_high();
        } else {
            high.insert(num);
        }
    }

    void pop(int num){
        auto itLow = low.find(num);
        if (itLow != low.end()){
            S -= num;
            low.erase(itLow);
            if (low.size() < K && !high.empty())
                move_high_min_to_low();
        } else {
            auto itHigh = high.find(num);
            high.erase(itHigh);
        }
    }

};

class Solution {
public:
    long long minimumCost(vector<int>& nums, int k, int dist) {
        KHeap h(k - 1);
        for (int i = 1; i <= dist; i++)
            h.push(nums[i]);
        long long ans = 1e15;
        for (int i = 1; i + k - 1 <= nums.size(); i++){
            if (i + dist < nums.size())
                h.push(nums[i + dist]);
            ans = min(ans, h.top());
            // cout << h.size() << ", " << h.top() << endl;
            h.pop(nums[i]);
        }
        return ans + nums[0];
    }
};