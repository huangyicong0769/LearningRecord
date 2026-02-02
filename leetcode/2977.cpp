#include "lc.hpp"

struct Trie{
    Trie* child[26];
    int id;

    Trie(){
        for (int i = 0; i < 26; i++)
            child[i] = nullptr;
        id = -1;
    }
};

int add(Trie* node, const string &word, int &index){
    for (char ch : word){
        if (!node->child[ch - 'a'])
            node->child[ch - 'a'] = new Trie();
        node = node->child[ch - 'a'];
    }
    if (node->id == -1)
        node->id = ++index;
    return node->id;
}

class Solution {
    const int INF = INT_MAX/2;
public:
    long long minimumCost(string source, string target, vector<string>& original, vector<string>& changed, vector<int>& cost) {
        const int N = source.size();
        const int M = original.size();
        Trie* root = new Trie();

        vector<vector<int>> G(M * 2, vector<int>(M * 2, INF));
        for (int i = 0; i < 2 * M; i++)
            G[i][i] = 0;
        int p = -1;
        for (int i = 0; i < M; i++){
            int x = add(root, original[i], p);
            int y = add(root, changed[i], p);
            G[x][y] = min(G[x][y], cost[i]);
        }

        for (int k = 0; k <= p; k++)
            for (int i = 0; i <= p; i++)
                for (int j = 0; j <= p; j++)
                    G[i][j] = min(G[i][j], G[i][k] + G[k][j]);

        vector<long long> f(N, -1);
        for (int j = 0; j < N; j++){
            if (j > 0 && f[j - 1] == -1)
                continue;
            if (source[j] == target[j])
                f[j] = (f[j] == -1 ? (j > 0 ? f[j - 1] : 0) : min(f[j], (j > 0 ? f[j - 1] : 0)));
            Trie *u = root, *v = root;
            for (int i = j; i < N; i++){
                u = u->child[source[i] - 'a'];
                v = v->child[target[i] - 'a'];
                if (!u || !v)
                    break;
                if (u->id == -1 || v->id == -1 || G[u->id][v->id] == INF)
                    continue;
                f[i] = (f[i] == -1 ? ((j > 0 ? f[j - 1] : 0) + G[u->id][v->id]) : min(f[i], (j > 0 ? f[j - 1] : 0) + G[u->id][v->id]));
            }
        }
        return f[N - 1];
    }
};