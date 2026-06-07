#include "lc.hpp"

class Solution {
public:
    TreeNode* createBinaryTree(vector<vector<int>>& descriptions) {
        std::vector<TreeNode*> nodes(100001, nullptr);
        std::vector<char> isChild(100001, 0);
        for (const auto& desc : descriptions) {
            int parent = desc[0], child = desc[1], isLeft = desc[2];
            if (!nodes[parent]) {
                nodes[parent] = new TreeNode(parent);
            }
            if (!nodes[child]) {
                nodes[child] = new TreeNode(child);
            }
            if (isLeft) {
                nodes[parent]->left = nodes[child];
            } else {
                nodes[parent]->right = nodes[child];
            }
            isChild[child] = 1;
        }
        for (const auto& desc : descriptions) {
            int parent = desc[0];
            if (!isChild[parent]) {
                return nodes[parent];
            }
        }
        return nullptr;
    }
};