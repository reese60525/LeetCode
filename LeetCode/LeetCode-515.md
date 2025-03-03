# <center> [515. Find Largest Value in Each Tree Row](https://leetcode.com/problems/find-largest-value-in-each-tree-row/description/) </center>

## 題目敘述

[![](https://i.imgur.com/cjOgBqW.png)](https://i.imgur.com/cjOgBqW.png)

給一個 binary tree，找出每一層最大的值。

## 解題思路

### 1. Depth First Search（DFS）

令陣列 `res` 為要回傳的答案，`res[i]` 表示第 `i` 層的最大值，用 DFS 遍歷每個 branch，並且記錄從 0 開始的深度 `level`，有以下兩種情況：

- $level = res\_size$ ，表示該層還沒有任何 value 在 `res[level]` 中，將該值放入 `res[level]`。

- $level < res\_size$ ，則將當前節點的值和 `res[level]` 比較大小，將較大的值放入 `res[level]`。

#### 程式碼

```cpp {.line-numbers}
// struct TreeNode {
//     int val;
//     TreeNode *left;
//     TreeNode *right;
//     TreeNode() : val(0), left(nullptr), right(nullptr) {}
//     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
//     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
// };

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
```

[![](https://i.imgur.com/2BQZzvG.png)](https://i.imgur.com/2BQZzvG.png)

#### 複雜度分析

令 $n$ 為節點的數量。

- 時間複雜度： $O(n)$

- 空間複雜度： $O(n)$

### 2. BFS

遍歷每一層，找出最大值。

#### 程式碼

```cpp {.line-numbers}
// struct TreeNode {
//     int val;
//     TreeNode *left;
//     TreeNode *right;
//     TreeNode() : val(0), left(nullptr), right(nullptr) {}
//     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
//     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
// };

class Solution {
  public:
    std::vector<int> largestValues(TreeNode *root) {
        std::queue<TreeNode *> q;
        // 處理空樹的情況
        if (root) {
            q.push(root);
        }

        std::vector<int> res;
        while (!q.empty()) {
            int q_size = q.size();
            int max_val = INT_MIN;

            while (q_size--) {
                TreeNode *node = q.front();
                q.pop();
                max_val = std::max(max_val, node->val);

                if (node->left) {
                    q.push(node->left);
                }
                if (node->right) {
                    q.push(node->right);
                }
            }

            res.push_back(max_val);
        }

        return res;
    }
};
```

[![](https://i.imgur.com/Z8WKAXs.png)](https://i.imgur.com/Z8WKAXs.png)

#### 複雜度分析

令 $n$ 為節點的數量。

- 時間複雜度： $O(n)$

- 空間複雜度： $O(n)$
