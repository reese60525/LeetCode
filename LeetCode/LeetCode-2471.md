# <center> [2471. Minimum Number of Operations to Sort a Binary Tree by Level](https://leetcode.com/problems/minimum-number-of-operations-to-sort-a-binary-tree-by-level/description/) </center>

## 題目敘述

[![](https://i.imgur.com/FDSjFG8.png)](https://i.imgur.com/FDSjFG8.png)

給一個 value 不重複的 binary tree，對每一層的節點進行升序排序，請問最少需要幾次交換節點的操作才能將整個 tree 每層都排序。

## 解題思路

### 1. BFS and Simulation

BFS 每一層的節點，將節點的值和 index 存入一個整數陣列 `vec` 中，對 `vec` 排序，然後模擬將排序後的 `vec` 復原至排序前的 `vec`，如果排序後的 `vec[i]` 其 `i` 不等於排序前的 index，則需要將該節點換到原本的位置，直到節點當前 index 和原本的一樣。

#### 程式碼

```cpp {.line-numbers}
/*
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
```

Permutation Cycle 的概念：

[![](https://i.imgur.com/B479xqZ.png)](https://i.imgur.com/B479xqZ.png)

因為題目並沒有要求要將節點的值改變，只需要計算交換次數，因此可以用 Permutation Cycle 的概念來計算交換次數，而每個 cycle 的邊數量 - 1 就是該 cycle 的最小交換次數，因此可以把以下 code 改寫：

```cpp {.line-numbers}
// 模擬還原排序後的節點
std::sort(vec.begin(), vec.end());
for (size_t i = 0; i < vec.size(); ++i) {
    // 如果當前節點 index 不是原本的 index，則需要交換
    while (vec[i].second != i) {
        std::swap(vec[i], vec[vec[i].second]);
        ++res;
    }
}
```

這段 code 能替換成

```cpp {.line-numbers}
std::vector<bool> visited(q_size, false);
std::sort(vec.begin(), vec.end());
for (size_t i = 0; i < vec.size(); ++i) {
    if (visited[i]) {
        continue;
    }

    int j = i; // 從當前節點找 cycle
    while (!visited[j]) {
        ++res; // cycle 的邊數量
        visited[j] = true;
        j = vec[j].second;
    }
    --res; // cycle 邊數量 - 1 = 最小交換次數
}
```

[![](https://i.imgur.com/gmaLsRQ.png)](https://i.imgur.com/gmaLsRQ.png)

#### 複雜度分析

令 $n$ 為節點的數量。

- 時間複雜度： $O(n \log n)$

- 空間複雜度： $O(n)$
