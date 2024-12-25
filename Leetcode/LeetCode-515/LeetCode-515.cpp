/*
 *  Author      : Reese
 *  Created On  : 2024-12-25 09:13
 *  Description : https://leetcode.com/problems/find-largest-value-in-each-tree-row/description/
 */

#include <iostream>
#include <queue>
#include <vector>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

// DFS
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
    std::vector<int> res;

    void dfs(TreeNode *cur, int level) {
        if (cur == nullptr) {
            return;
        }

        if (level == res.size()) {
            res.push_back(cur->val);
        }
        else {
            res[level] = std::max(res[level], cur->val);
        }

        dfs(cur->left, level + 1);
        dfs(cur->right, level + 1);
    }

    std::vector<int> largestValues(TreeNode *root) {
        dfs(root, 0);

        return res;
    }
};

// // BFS
// struct TreeNode {
//     int val;
//     TreeNode *left;
//     TreeNode *right;
//     TreeNode() : val(0), left(nullptr), right(nullptr) {}
//     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
//     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
// };
//
// class Solution {
//   public:
//     std::vector<int> largestValues(TreeNode *root) {
//         std::queue<TreeNode *> q;
//         // 處理空樹的情況
//         if (root) {
//             q.push(root);
//         }

//         std::vector<int> res;
//         while (!q.empty()) {
//             int q_size = q.size();
//             int max_val = INT_MIN;

//             while (q_size--) {
//                 TreeNode *node = q.front();
//                 q.pop();
//                 max_val = std::max(max_val, node->val);

//                 if (node->left) {
//                     q.push(node->left);
//                 }
//                 if (node->right) {
//                     q.push(node->right);
//                 }
//             }

//             res.push_back(max_val);
//         }

//         return res;
//     }
// };

int main() {

    return 0;
}