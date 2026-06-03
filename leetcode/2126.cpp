#include "lc.hpp"

class Solution {
public:
    bool asteroidsDestroyed(int mass, vector<int>& asteroids) {
        std::sort(asteroids.begin(), asteroids.end());
        for (int i = 0; i < asteroids.size(); i++){
            if (mass < asteroids[i])
                return false;
            mass += asteroids[i];
        }
        return true;
    }
};