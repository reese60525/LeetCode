/*
 * 題目: https://leetcode.com/problems/evaluate-boolean-binary-tree/description/
 *
 * 題目解釋:
 * 給一個full binary tree，full binary tree表示每個node只有0或2個children，當一個node沒有children
 * 時稱之為leaf node，而每個node的值為0~3，0表示false，1表示true，2表示or，3表示and，對所有的leaf node
 * 根據其parent進行and or運算後，其parent的value會變成運算後的結果(0或1)，回傳把所有運算做完後的結果。
 *
 * 思路:
 * dfs遍歷節點，當current node值為0或1則回傳值，若為2或3則遞迴找其左右children的值並回傳運算結果。
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
    bool evaluateTree(TreeNode *root) {
        if (root->val == 1)
            return true;
        if (root->val == 0)
            return false;
        if (root->val == 2)
            return evaluateTree(root->left) or evaluateTree(root->right);
        if (root->val == 3)
            return evaluateTree(root->left) and evaluateTree(root->right);

        return true;
    }
};
int main() {

    return 0;
}