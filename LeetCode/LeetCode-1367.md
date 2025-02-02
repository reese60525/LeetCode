# <center> [1367. Linked List in Binary Tree](https://leetcode.com/problems/linked-list-in-binary-tree/description/) </center>

## 題目敘述

[![](https://i.imgur.com/9mzp1NJ.png)](https://i.imgur.com/9mzp1NJ.png)

給一個 binary tree 和一個 linked list，判斷 binary tree 中是否存在一個路徑，其順序和 linked list 相同。

## 解題思路

### 1. DFS

以 binary tree 中每一個節點為路徑起點，對每個路徑做 DFS 來判斷該路徑是否能和 linked list 相同。

要取得 binary tree 每個節點，可以用題目給的 `isSubPath function` 來當作 DFS 走訪 binary tree 所有節點，對於每個節點，將其傳入一個 DFS 來判斷以該節點為起點的路徑是否和 linked list 相同。

#### 程式碼

```cpp {.line-numbers}
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

        // 遍歷所有節點，將其當作起始點呼叫 dfs 判斷是否存在子路徑和 list 相同
        return dfs(dfs, head, root) ? true : isSubPath(head, root->left) || isSubPath(head, root->right);
    }
};
```

[![](https://i.imgur.com/YOFRpNF.png)](https://i.imgur.com/YOFRpNF.png)

#### 複雜度分析

令 $n$ 為 binary tree 的節點數， $m$ 為 linked list 的節點數， $h$ 為 binary tree 的高度。

- 時間複雜度： $O(n \cdot m)$

- 空間複雜度： $O(h)$

    考慮到當前節點的樹的深度為 $x$ ，對於該節點要去 DFS 匹配 list 還需要 $y$ 的遞迴深度，而 $y$ 取決於 list 和從該節點開始的子樹高度，因此 $y$ 會被整顆樹的高度所限制， $x + y$ 必然小於樹高度 $h$ 。

---

可以將兩個 DFS 改成一個 DFS 來處理。

每次進入到一個新的節點時，有兩種路徑選擇，第一個是延續之前的路徑繼續找，第二個是以當前節點的左右子樹為起點來找。所以每個節點都會被當作路徑起點來和 list 比對。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    bool isSubPath(ListNode *head, TreeNode *root) {
        auto dfs = [&](auto &&dfs, ListNode *list, TreeNode *node) -> bool {
            // list 為空，表示匹配完了，回傳 true
            if (list == nullptr) {
                return true;
            }
            // tree 為空，表示匹配失敗，回傳 false
            if (node == nullptr) {
                return false;
            }

            bool c1 = false, c2 = false;
            // 延續之前的路徑繼續找
            if (list->val == node->val) {
                c1 = dfs(dfs, list->next, node->left) || dfs(dfs, list->next, node->right);
            }
            // 以子樹的 root 為起點來找，要注意的是只有 list 為 head 時才會進行這個判斷
            // 這是避免每個 node 新闢的分支又以自身為起點找，這樣會造成重複的計算
            if (list == head) {
                c2 = dfs(dfs, head, node->left) || dfs(dfs, head, node->right);
            }

            return c1 || c2;
        };

        return dfs(dfs, head, root);
    }
};
```

[![](https://i.imgur.com/I0z2iFU.png)](https://i.imgur.com/I0z2iFU.png)

#### 複雜度分析

令 $n$ 為 binary tree 的節點數， $m$ 為 linked list 的節點數， $h$ 為 binary tree 的高度。

- 時間複雜度： $O(n \cdot m)$

- 空間複雜度： $O(h)$

---

有一種空間優化的方式，是將已經丟入 DFS 確認路徑的節點設為 `nullptr` ，根據 chatGPT 的說法，被拋棄的節點不會占用遞迴的 stack 空間，所以可以節省空間，我自己也不清楚為什麼，但實際測試下來確實空間使用量有下降。

#### 程式碼

```cpp {.line-numbers}
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
```

[![](https://i.imgur.com/E4Vbcjg.png)](https://i.imgur.com/E4Vbcjg.png)

#### 複雜度分析

令 $n$ 為 binary tree 的節點數， $m$ 為 linked list 的節點數， $h$ 為 binary tree 的高度。

- 時間複雜度： $O(n \cdot m)$

- 空間複雜度： $O(h)$
