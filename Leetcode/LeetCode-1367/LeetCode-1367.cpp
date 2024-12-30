/*
 *  Author      : Reese
 *  Created On  : 2024-12-30 17:20
 *  Description : https://leetcode.com/problems/linked-list-in-binary-tree/description/
 */

#include <cstdlib>
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

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
    bool isSubPath(ListNode *head, TreeNode *root) {
        if (root == nullptr) {
            return false;
        }

        // 用於判斷當前路徑是否和 list 相同
        auto dfs = [&](auto &&dfs, ListNode *list, TreeNode *node) -> bool {
            // list 為空表示 list 都配對完，有找到一個路徑和 list 相同
            if (list == nullptr) {
                return true;
            }
            // 當前節點為空表示 list 長度大於樹，不可能有相同路徑
            // 又或者是當前 value 匹配失敗
            if (node == nullptr || node->val != list->val) {
                return false;
            }
            // 繼續往下找
            return dfs(dfs, list->next, node->left) || dfs(dfs, list->next, node->right);
        };

        // 找到一個路徑和 list 相同，直接回傳 true
        if (dfs(dfs, head, root)) {
            return true;
        }

        // 沒找到，以別的節點當起始點繼續找
        bool res = isSubPath(head, root->left) || isSubPath(head, root->right);

        // 設為 nullptr，這是空間使用量降低的關鍵
        root->left = root->right = nullptr;
        // 有沒有都沒影響，我不知道為什麼
        delete (root->left);
        delete (root->right);

        return res;
    }
};

// // 兩個 DFS 解法
// class Solution {
//   public:
//     bool isSubPath(ListNode *head, TreeNode *root) {
//         if (root == nullptr) {
//             return false;
//         }

//         // 用於判斷當前路徑是否和 list 相同
//         auto dfs = [&](auto &&dfs, ListNode *list, TreeNode *node) -> bool {
//             // list 為空表示 list 都配對完，有找到一個路徑和 list 相同
//             if (list == nullptr) {
//                 return true;
//             }
//             // 當前節點為空表示 list 長度大於樹，不可能有相同路徑，或是路徑匹配失敗
//             if (node == nullptr || node->val != list->val) {
//                 return false;
//             }
//             // 繼續往下找，只要找到一個路徑和 list 相同就回傳 true
//             return dfs(dfs, list->next, node->left) || dfs(dfs, list->next, node->right);
//         };

//         // 遍歷所有節點，將其當作起始點呼叫 dfs 判斷是否存在子路徑和 list 相同
//         return dfs(dfs, head, root) ? true : isSubPath(head, root->left) || isSubPath(head, root->right);
//     }
// };

// 兩個 DFS 解法
// class Solution {
//   public:
//     bool isSubPath(ListNode *head, TreeNode *root) {
//         // 用於判斷當前路徑是否和 list 相同
//         auto dfs = [&](auto &&dfs, ListNode *list, TreeNode *node) -> bool {
//             // list 為空表示 list 都配對完，有找到一個路徑和 list 相同
//             if (list == nullptr) {
//                 return true;
//             }
//             // 當前節點為空表示 list 長度大於樹，不可能有相同路徑，或是路徑匹配失敗
//             if (node == nullptr || node->val != list->val) {
//                 return false;
//             }
//             // 繼續往下找，只要找到一個路徑和 list 相同就回傳 true
//             return dfs(dfs, list->next, node->left) || dfs(dfs, list->next, node->right);
//         };
//         // 遍歷所有節點，將其當作起始點呼叫 dfs 判斷是否存在子路徑和 list 相同
//         auto getNode = [&](auto &&getNode, TreeNode *root) -> bool {
//             if (root == nullptr) {
//                 return false;
//             }
//             // 找到一個路徑和 list 相同就回傳 true，否則以子樹的節點當作起始點繼續找
//             return dfs(dfs, head, root) ? true : getNode(getNode, root->left) || getNode(getNode, root->right);
//         };

//         return getNode(getNode, root);
//     }
// };

// 單個 DFS 解法
// class Solution {
//   public:
//     bool isSubPath(ListNode *head, TreeNode *root) {
//         auto dfs = [&](auto &&dfs, ListNode *list, TreeNode *node) -> bool {
//             // list 為空，表示匹配完了，回傳 true
//             if (list == nullptr) {
//                 return true;
//             }
//             // tree 為空，表示匹配失敗，回傳 false
//             if (node == nullptr) {
//                 return false;
//             }

//             bool c1 = false, c2 = false;
//             // 延續之前的路徑繼續找
//             if (list->val == node->val) {
//                 c1 = dfs(dfs, list->next, node->left) || dfs(dfs, list->next, node->right);
//             }
//             // 以當前節點為起點來找，要注意的是只有 list 為 head 時才會進行這個判斷
//             // 這是避免每個 node 新闢的分支又開始以自身為起點找，這樣會造成重複的計算
//             if (list == head) {
//                 c2 = dfs(dfs, head, node->left) || dfs(dfs, head, node->right);
//             }

//             return c1 || c2;
//         };

//         return dfs(dfs, head, root);
//     }
// };

int main() {

    return 0;
}