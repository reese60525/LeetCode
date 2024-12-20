/*
 *  Author      : Reese
 *  Created On  : 2024-12-20 11:34
 *  Description : https://leetcode.com/problems/reverse-odd-levels-of-binary-tree/description/
 */

#include <iostream>
#include <queue>
#include <vector>

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

// // bfs
// class Solution {
//   public:
//     TreeNode *reverseOddLevels(TreeNode *root) {
//         bool is_odd = false;
//         std::vector<TreeNode *> tmp;
//         std::queue<TreeNode *> q;
//         q.push(root);

//         while (!q.empty()) {
//             int size = q.size();

//             for (int i = 0; i < size; ++i) {
//                 if (is_odd) {
//                     tmp.push_back(q.front());
//                 }
//                 if (q.front()->left != nullptr && q.front()->right != nullptr) {
//                     q.push(q.front()->left);
//                     q.push(q.front()->right);
//                 }
//                 q.pop();
//             }

//             // 當前是 odd level 就將該 level 的 node value reverse
//             if (is_odd) {
//                 for (int i = 0; i < size / 2; ++i) {
//                     std::swap(tmp[i]->val, tmp[size - 1 - i]->val);
//                 }
//             }

//             is_odd = !is_odd;
//             tmp.clear();
//         }

//         return root;
//     }
// };

// dfs
class Solution {
  public:
    void dfs(TreeNode *left_node, TreeNode *right_node, bool is_odd) {
        if (left_node != nullptr && right_node != nullptr) {
            if (is_odd) {
                std::swap(left_node->val, right_node->val);
            }
            // 左右子樹往外擴散
            dfs(left_node->left, right_node->right, !is_odd);
            // 左右子樹往內擴散
            dfs(left_node->right, right_node->left, !is_odd);
        }
    }

    TreeNode *reverseOddLevels(TreeNode *root) {
        dfs(root->left, root->right, true);

        return root;
    }
};

int main() {

    return 0;
}