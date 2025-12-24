#include <vector>
#include <map>
using namespace std;

class Solution {
public:
    int maxTwoEvents(vector<vector<int>>& events) {
        int ans = -1;
        map<int, int> surfix;

        for (const auto &event : events){
            ans = std::max(ans, event[2]);
            surfix[event[0]] = std::max(surfix[event[0]], event[2]);
        }
        
        for (auto i = std::prev(surfix.end()); i != surfix.begin(); i = std::prev(i)){
            std::prev(i)->second = std::max(std::prev(i)->second, i->second);
        }

        for (const auto & event : events){
            auto it = surfix.upper_bound(event[1]);
            if (it != surfix.end())
                ans = max(ans, event[2] + it->second);
        }

        return ans;
    }
};