#include <string>
#include <vector>
#include <queue>
#include <iostream>
using namespace std;

class Solution {
    std::unique_ptr<vector<int>> status;

    constexpr int A2I(const string &s){
        return std::stoi(s);
    }

    vector<int> getID(const string & id){
        vector<int> ret;
        string tmp = "";
        for (const char & ch : id){
            if (ch == ' '){
                ret.push_back(A2I(tmp));
                tmp = "";
            }else{
                if (ch >= '0' && ch <= '9')
                    tmp += ch;
            }
        }
        if (tmp != "")
            ret.push_back(A2I(tmp));
            
        return std::move(ret);
    }

    constexpr int getTimestamp(const string & timestamp){
        return A2I(timestamp);
    }

    constexpr void printEvent(const vector<string> & event){
        cout << "{" << event[0] << ", " << event[1] << ", " << event[2] << "}"; 
    }

public:
    vector<int> countMentions(int numberOfUsers, vector<vector<string>>& events) {
        sort(events.begin(), events.end(), [&](const auto &a, const auto &b)->bool{
            int c = A2I(a[1]), d = A2I(b[1]);
            return c < d || c == d && a[0][0] > b[0][0];
        });

        // for (auto &event:events){
        //     printEvent(event);
        //     cout << ",";
        // }
        // cout << endl;

        this->status = std::make_unique<vector<int>> (numberOfUsers, 1);

        queue<pair<int, int>> onlineEvents;
        auto eventsHead = events.begin();
        vector<int> mentions(numberOfUsers, 0);

        while (eventsHead != events.end()){
            if (!onlineEvents.empty() && onlineEvents.front().first <= getTimestamp((*eventsHead)[1])){
                (*(this->status))[onlineEvents.front().second] = 1;
                onlineEvents.pop();
            }else{
                auto & currentEvent = eventsHead;
                if ((*currentEvent)[0][0] == 'M'){
                    auto timestamp = getTimestamp((*currentEvent)[1]);
                    if ((*currentEvent)[2][0] == 'A'){
                        for (int id = 0; id < numberOfUsers; id++)
                            mentions[id]++;
                    }else if ((*currentEvent)[2][0] == 'H'){
                        for (int id = 0; id < numberOfUsers; id++)
                            mentions[id] += this->status->at(id);
                    }else {
                        for (int &id : getID((*currentEvent)[2]))
                            mentions[id]++;
                    }
                }else if ((*currentEvent)[0][0] == 'O'){
                    auto timestamp = getTimestamp((*currentEvent)[1]);
                    auto id = A2I((*currentEvent)[2]);
                    (*(this->status))[id] = 0;
                    onlineEvents.push({timestamp + 60, id});
                }
                currentEvent = std::next(currentEvent);
            }
        }
        return std::move(mentions);
    }
};