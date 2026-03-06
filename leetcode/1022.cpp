#include "lc.hpp"

class Solution {
public:
    int sumRootToLeaf(TreeNode* root) {
        return dfs(root, 0);
    }
    int dfs(TreeNode* x, int a){
        a = (a << 1) + x->val;
        if (!x -> left && !x->right)
            return a;
        int ret = 0;
        if (x->left)
            ret += dfs(x->left, a);
        if (x->right)
            ret += dfs(x->right, a);
        return ret;
    }
};