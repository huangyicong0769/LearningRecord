#include <iostream>
#include <vector>
#include <string>
#include <string_view>
#include <algorithm>
#include <numeric>
#include <queue>
#include <map>
#include <set>
#include <unordered_set>
#include <tuple>
#include <ranges>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};