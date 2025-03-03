# <center> [2415. Reverse Odd Levels of Binary Tree](https://leetcode.com/problems/reverse-odd-levels-of-binary-tree/submissions/1483423209/?envType=daily-question&envId=2024-12-20) </center>

## 題目敘述

[![](https://i.imgur.com/Wf154mv.png)](https://i.imgur.com/Wf154mv.png)

給一個 perfect binary tree，將 odd level 的所有 node value 反轉。

perfect binary tree 定義：

- 所有 parent node 都有兩個 children node。

- 所有 leaf node 都在同個 level。

## 解題思路

### 1. BFS

使用 BFS 將每個 level 的 node 存入 queue 和 vector 中，如果當前是 odd level，則 reverse vector 中的 node value。

#### 程式碼

```cpp {.line-numbers}
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

class Solution {
  public:
    TreeNode *reverseOddLevels(TreeNode *root) {
        bool is_odd = false;
        std::vector<TreeNode *> tmp;
        std::queue<TreeNode *> q;
        q.push(root);

        while (!q.empty()) {
            int size = q.size();

            for (int i = 0; i < size; ++i) {
                if (is_odd) {
                    tmp.push_back(q.front());
                }
                if (q.front()->left != nullptr && q.front()->right != nullptr) {
                    q.push(q.front()->left);
                    q.push(q.front()->right);
                }
                q.pop();
            }

            // 當前是 odd level 就將該 level 的 node value reverse
            if (is_odd) {
                for (int i = 0; i < size / 2; ++i) {
                    std::swap(tmp[i]->val, tmp[size - 1 - i]->val);
                }
            }

            is_odd = !is_odd;
            tmp.clear();
        }

        return root;
    }
};
```

[![](https://i.imgur.com/h4NHp1M.png)](https://i.imgur.com/h4NHp1M.png)

#### 複雜度分析

令 $n$ 為 node 數量， $w$ 為 tree 的最大寬度。

- 時間複雜度： $O(n)$

- 空間複雜度： $O(w)$

    在 perfect binary tree 中 $w \approx \frac{n}{2}$ 。

### 2. DFS

用 dfs 遞迴遍歷 tree，當前是 odd level 就將當前左右對應的 node value 交換。

**要特別注意的是 DFS 寫法只適用於 perfect binary tree**

#### 程式碼

```cpp {.line-numbers}
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

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
```

[![](https://i.imgur.com/4KumM5Y.png)](https://i.imgur.com/4KumM5Y.png)

#### 複雜度分析

令 $n$ 為 node 數量， $h$ 為 tree 的高度。

- 時間複雜度： $O(n)$

- 空間複雜度： $O(h)$

    遞迴使用的空間由遞迴堆疊決定，如果是 perfect binary tree，則 $h = \log_2(n)$ ，如果是傾斜的 binary tree，最壞情況 $h = n$ 。
