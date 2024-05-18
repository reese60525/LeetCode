/*
 * 題目: https://leetcode.com/problems/delete-leaves-with-a-given-value/description/
 *
 * 題目解釋:
 * 把所有value和target相同的leaf node刪除
 *
 * 思路:
 * dfs遍歷，若l和r都為nullptr即為leaf node，再判斷value是否和target相等，是的話return nullptr，
 * 反之return原本的root。
 *
 * 解法:
 * 如上所說。
 */
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
  public:
    TreeNode *removeLeafNodes(TreeNode *root, const int &target) {
        // 當前為nullptr
        if (!root) {
            return root;
        }
        // left和right會一直找直到nullptr，到leaf node之後才會進行刪除判斷
        root->left = removeLeafNodes(root->left, target);
        root->right = removeLeafNodes(root->right, target);
        // 判斷node是否能刪除，能的話就return nullptr，這樣其parent也能把l或r更新為nullptr
        if (root->val == target && !root->left && !root->right) {
            return nullptr;
        }
        // 若node不能刪除return傳進來時的root
        return root;
    }
};

int main() {

    return 0;
}