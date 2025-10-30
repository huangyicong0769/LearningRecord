#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class Solution1 {
public:
    int minNumberOperations(vector<int>& target) {
        stack<int> s;
        int ans = 0;
        for (int& num : target){
            if (!s.empty() && num < s.top())
                ans += s.top() - num;
            while (!s.empty() && num < s.top())
                s.pop();
            s.push(num);
        }
        return ans + s.top();
    }
};

class Solution2 {
public:
    int minNumberOperations(vector<int>& target) {
        int ans = *target.begin();
        for (auto it = target.begin() + 1; it < target.end(); it++)
            ans += std::max(0, *it - *(it-1));
        return ans;
    }
};