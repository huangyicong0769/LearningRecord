#include "lc.hpp"

class Solution {
public:
    vector<int> longestRepeating(
        string s,
        string queryCharacters,
        vector<int>& queryIndices
    ) {
        const int N = s.size();

        std::set<int> cut{0, N};
        std::multiset<int> len;

        for (int i = 1; i < N; i++)
            if (s[i] != s[i - 1])
                cut.insert(i);

        for (auto it = cut.begin(), pre = it++; it != cut.end(); pre = it++)
            len.insert(*it - *pre);

        auto addCut = [&](int x) {
            auto r = cut.lower_bound(x);
            auto l = std::prev(r);

            len.erase(len.find(*r - *l));

            len.insert(x - *l);
            len.insert(*r - x);

            cut.insert(x);
        };

        auto removeCut = [&](int x) {
            auto it = cut.find(x);
            auto l = std::prev(it);
            auto r = std::next(it);

            len.erase(len.find(x - *l));
            len.erase(len.find(*r - x));

            len.insert(*r - *l);

            cut.erase(it);
        };

        // 根据当前 s 判断 x 这个分界点是否应该存在
        auto updateCut = [&](int x) {
            if (x <= 0 || x >= N)
                return;

            bool shouldExist = s[x - 1] != s[x];
            bool exists = cut.contains(x);

            if (shouldExist && !exists)
                addCut(x);
            else if (!shouldExist && exists)
                removeCut(x);
        };

        std::vector<int> ans;
        ans.reserve(queryIndices.size());

        for (int q = 0; q < queryIndices.size(); q++) {
            int p = queryIndices[q];
            char c = queryCharacters[q];

            if (s[p] != c) {
                s[p] = c;

                // 修改 p 只会影响这两条边
                updateCut(p);
                updateCut(p + 1);
            }

            ans.push_back(*len.rbegin());
        }

        return ans;
    }
};