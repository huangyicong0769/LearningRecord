#include <vector>
#include <numeric>
using namespace std;

class Solution {
public:
    int minimumBoxes(vector<int>& apple, vector<int>& capacity) {
        int apples = std::accumulate(apple.begin(), apple.end(), 0);
        sort(capacity.begin(), capacity.end(), std::greater<int>());
        for (int i = 0; i < capacity.size(); i++){
            if (apples <= 0) return i;
            apples -= capacity[i];
        }
        return capacity.size();
    }
};