#include <string>
#include <set>
#include <queue>
using namespace std;

class Solution {
public:
    string findLexSmallestString(string s, int a, int b) {
        queue<string> q;
        set<string> hash;
        q.push(s);
        hash.insert(s);
        while(q.size()){
            string cur = q.front();
            q.pop();
            string tmp = handleA(cur, a);
            if (hash.find(tmp) == hash.end()){
                q.push(tmp);
                hash.insert(tmp);
            }
            tmp = handleB(cur, b);
            if (hash.find(tmp) == hash.end()){
                q.push(tmp);
                hash.insert(tmp);
            }
        }
        return *hash.begin();
    }
private:
    string handleA(string str, int a){
        for (int i = 0; i < str.size(); i++){
            if (i % 2 == 0) continue;
            str[i] = (str[i] - '0' + a)%10 + '0';
        }
        return str;
    }
    string handleB(string str, int b){
        string tmp = str;
        for (int i = 0; i < str.size(); i++)
            tmp[i] = str[(i - b + str.size())%str.size()];
        return tmp;
    }
};

int main(){

}