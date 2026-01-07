#include <algorithm>
#include <vector>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
    const int M = 1e9 + 7;
    std::vector<long long> sums;
public:
    int maxProduct(TreeNode* root) {
        sums.clear();
        long long totalSum = dfs(root);
        long long ans = 0;
        for (long long s : sums) {
            ans = std::max(ans, s * (totalSum - s));
        }
        return ans % M;
    }

    long long dfs(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }
        long long curSum = root->val + dfs(root->left) + dfs(root->right);
        sums.push_back(curSum);
        return curSum;
    }
};