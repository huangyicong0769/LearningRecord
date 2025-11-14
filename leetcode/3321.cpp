#include <map>
#include <set>
#include <vector>
#include <iostream>
using namespace std;

class Solution {
    std::unordered_map<int, int> f;
    std::set<pair<int, int>> s1, s2;
    long long s, tsum;
    int x;
public:
    vector<long long> findXSum(vector<int>& nums, int k, int x) {
        std::vector<long long> ans;
        s = 0;
        this->x = x;
        for (int i = 0; i < k - 1; i++){
            f[nums[i]] += 1;
            s += nums[i];
        }
        tsum = 0;
        for (auto &p:f)
            add(make_pair(p.second, p.first));
        cout << "s1: "; print(s1);
        cout << "s2: "; print(s2);
        if (nums.size() < 10) cout << s2.size() << ' ' << s << ' ' << tsum << endl;
        for (int i = 0; i <= nums.size() - k; i++){
            cout << "===" << endl << i << ":" << endl;
            modify(nums[i + k - 1], 1LL);
            cout << "s1: "; print(s1);
            cout << "s2: "; print(s2);
            if (nums.size() < 10) cout << s2.size() << ' ' << s << ' ' << tsum << endl;
            if (s2.size() < x)
                ans.push_back(s);
            else ans.push_back(tsum);
            modify(nums[i], -1LL);
        }
        return ans;
    }
    void add(pair<int, int> p){
        if (s2.size() < x) {
            s2.insert(p);
            tsum += (long long)p.first*p.second;
        }else{
            if (*s2.begin() < p){
                tsum -= (long long)s2.begin()->first*s2.begin()->second;
                s1.insert(*s2.begin());
                s2.erase(s2.begin());
                s2.insert(p);
                tsum += (long long)p.first*p.second;
            }else
                s1.insert(p);
        }
    }
    void del(pair<int, int> p){
        std::set<pair<int, int>>::iterator it1, it2;
        if ((it1 = s1.find(p)) != s1.end()){
            s1.erase(it1);
        }
        if ((it2 = s2.find(p)) != s2.end()){
            tsum -= (long long)p.first*p.second;
            s2.erase(it2);
        }
        while (!s1.empty() && s2.size() < x){
            auto it = std::prev(s1.end());
            s2.insert(*it);
            tsum += (long long)it->first * it->second;
            s1.erase(it);
        }
    }
    void modify(int num, long long d){
        // cout << "---" << endl << "modify start" << ":" << endl;
        del(make_pair(f[num], num));
        f[num] += d;
        add(make_pair(f[num], num));
        s += d*num;
        // cout << "modify end" << "." << endl;
    }
    void print(set<pair<int, int>> &s){
        for (auto it : s)
            cout << it.first << ", " << it.second << "; ";
        cout << endl; 
    }
};