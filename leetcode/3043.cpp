#include "lc.hpp"

class Solution {
    struct trieNode{
        int child[10] = {0};
        bool word = false;
    };

    std::vector<trieNode> Trie;
    int tcnt = 0;

    void buildTrie(const std::vector<char> &x, int cnt, int node){
        if (cnt == -1){
            Trie[node].word = true;
            return;
        }
        int digit = x[cnt];
        if (Trie[node].child[digit] == 0){
            Trie.emplace_back();
            Trie[node].child[digit] = ++tcnt;
        }
        buildTrie(x, cnt - 1, Trie[node].child[digit]);
    }
    
    int LCP(const std::vector<char> &x, int cnt, int node){
        auto & n = Trie[node];
        if (cnt == -1 || n.child[x[cnt]] == 0){
            return 0;
        }
        return 1 + LCP(x, cnt - 1, n.child[x[cnt]]);
    }

public:
    int longestCommonPrefix(vector<int>& arr1, vector<int>& arr2) {
        Trie.clear();
        Trie.emplace_back();
        tcnt = 0;

        auto split = [](int x) -> std::vector<char> {
            std::vector<char> ret;
            do{
                ret.push_back(x % 10);
                x /= 10;
            }while(x);
            return ret;
        };

        for (auto & x : arr1){
            auto s = split(x);
            buildTrie(s, s.size() - 1, 0);
        }

        int ans = 0;
        for (auto & x : arr2){
            auto s = split(x);
            ans = std::max(ans, LCP(s, s.size() - 1, 0));
        }
        return ans;
    }
};

class SolutionOptimized {
    struct trieNode{
        int child[10] = {0};
    };

    std::vector<trieNode> Trie;
    int tcnt = 0;

    int highestPow10(int x){
        int p = 1;
        while (x >= 10){
            x /= 10;
            p *= 10;
        }
        return p;
    }

    void buildTrie(int x){
        int node = 0;
        int p = highestPow10(x);
        while (p > 0){
            int digit = x / p;
            int &next = Trie[node].child[digit];
            if (next == 0){
                Trie.emplace_back();
                next = ++tcnt;
            }
            node = next;
            x %= p;
            p /= 10;
        }
    }

    int LCP(int x){
        int node = 0;
        int p = highestPow10(x);
        int len = 0;
        while (p > 0){
            int digit = x / p;
            int next = Trie[node].child[digit];
            if (next == 0){
                break;
            }
            ++len;
            node = next;
            x %= p;
            p /= 10;
        }
        return len;
    }

public:
    int longestCommonPrefix(vector<int>& arr1, vector<int>& arr2) {
        Trie.clear();
        Trie.reserve(1 + static_cast<int>(arr1.size()) * 10);
        Trie.emplace_back();
        tcnt = 0;

        for (auto & x : arr1){
            buildTrie(x);
        }

        int ans = 0;
        for (auto & x : arr2){
            ans = std::max(ans, LCP(x));
        }
        return ans;
    }
};