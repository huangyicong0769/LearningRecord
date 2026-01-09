#include <vector>
#include <map>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
    std::unordered_map<int, std::vector<TreeNode*>> fathers;
    std::unordered_map<int, int> d;
    std::vector<TreeNode*> max_d;

    void dfs(TreeNode* root, TreeNode* father){
        if (father != nullptr)
            d[root->val] = d[father->val] + 1;
        else d[root->val] = 1;
        
        if (max_d.empty()) 
            max_d.push_back(root);
        else if (d[root->val] >= d[max_d[0]->val]){
            if (d[root->val] > d[max_d[0]->val]) 
                max_d.clear();
            max_d.push_back(root);
        }

        auto & far = fathers[root->val];
        if (father != nullptr) far.push_back(father);

        if (father != nullptr)
        for (int i = 0; i < fathers[far.back()->val].size(); i++)
            far.push_back(fathers[far.back()->val][i]);

        if (root->left != nullptr) dfs(root->left, root);
        if (root->right != nullptr) dfs(root->right, root);
    }

    TreeNode* LCA(TreeNode* a, TreeNode* b){
        // cout << a->val << ", " << b->val << endl;
        if (d[a->val] > d[b->val]) 
            std::swap(a, b);
        while (d[b->val] > d[a->val])
            for (int i = fathers[b->val].size() - 1; i >= 0; i--)
                if (d[fathers[b->val][i]->val] >= d[a->val]){
                    b = fathers[b->val][i];
                    break;
                }
        // cout << "!" << a->val << ", " << b->val << endl;
        for (int i = fathers[a->val].size() - 1; i >= 0 && a != b; i--)
            if (fathers[a->val][i] != fathers[b->val][i]){
                a = fathers[a->val][i];
                b = fathers[b->val][i];
                // cout << "?" << d[a->val] << ", " << d[b->val] << endl;
                i = min(i, (int)fathers[a->val].size());
            }
        return (a == b ? a : fathers[a->val][0]);
    }

public:
    TreeNode* subtreeWithAllDeepest(TreeNode* root) {
        dfs(root, nullptr);
        TreeNode* ans = max_d[0];
        for (int i = 1; i < max_d.size(); i++)
            ans = LCA(ans, max_d[i]);
        return ans;
    }
};