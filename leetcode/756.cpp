#include <string>
#include <vector>
#include <map>
using namespace std;

class Solution {
    std::unique_ptr<std::unordered_map<string, vector<char>>> allowed = nullptr;
    std::unordered_map<string, bool> status;
public:
    bool pyramidTransition(string bottom, vector<string>& allowed) {
        if (bottom.size() == 1) return true;
        if (status.find(bottom) != status.end())
            return status[bottom];
        if (this->allowed == nullptr){
            this->allowed = std::make_unique<std::unordered_map<string, vector<char>>>();
            for (const auto &s:allowed)
                (*this->allowed)[s.substr(0,2)].push_back(s.back());
        }
        vector<string> heads;
        heads.push_back("");
        for (int i = 1; i < bottom.size(); i++){
            const string &key = bottom.substr(i - 1, 2);
            if (this->allowed->find(key) == this->allowed->end())
                return status[bottom] = false;
            const vector<char> &candidates = (*this->allowed)[key];
            vector<string> new_heads;
            for (const string &head:heads)
                for (char c:candidates)
                    new_heads.push_back(head + c);
            heads = std::move(new_heads);
        }
        for (const string &head:heads)
            if (pyramidTransition(head, allowed))
                return status[bottom] = true;
        return status[bottom] = false;
    }
};