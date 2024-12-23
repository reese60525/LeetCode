/*
 *  Author      : Reese
 *  Created On  : 2024-12-23 08:11
 *  Description : https://leetcode.com/problems/minimum-number-of-operations-to-sort-a-binary-tree-by-level/description/
 */

#include <algorithm>
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

// 方法一： BFS + Simulation
class Solution {
  public:
    int minimumOperations(TreeNode *root) {
        std::queue<TreeNode *> q;
        q.push(root);

        int res = 0;
        while (!q.empty()) {
            size_t q_size = q.size();
            std::vector<std::pair<int, int>> vec(q_size); // 儲存每一層的節點和 index
            for (size_t i = 0; i < q_size; ++i) {
                TreeNode *node = q.front();
                q.pop();
                vec[i] = {node->val, i};

                if (node->left) {
                    q.push(node->left);
                }
                if (node->right) {
                    q.push(node->right);
                }
            }

            // 模擬還原排序後的節點
            std::sort(vec.begin(), vec.end());
            for (size_t i = 0; i < vec.size(); ++i) {
                // 如果當前節點 index 不是原本的 index，則需要交換
                while (vec[i].second != i) {
                    std::swap(vec[i], vec[vec[i].second]);
                    ++res;
                }
            }
        }

        return res;
    }
};

int main() {

    return 0;
}
