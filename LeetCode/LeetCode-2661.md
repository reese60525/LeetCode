# <center> [2661. First Completely Painted Row or Column](https://leetcode.com/problems/first-completely-painted-row-or-column/description/) </center>

## 題目敘述

[![](https://i.imgur.com/MHSXtMz.png)](https://i.imgur.com/MHSXtMz.png)

給一個長度為 $m \times n$ 的一維整數陣列 `arr` 和一個 $m \times n$ 的二維整數陣列 `mat`，其中 `arr` 和 `mat` 的 element 都是 $1$ 到 $m \times n$ 之間的整數，且沒有重複的數字。

從 $index = 0$ 開始遍歷 `arr`，將 `arr[i]` 的 element 對應到 `mat` 相同 element，將其標記為已經被走訪過，請問要讓 `mat` 的某一行或某一列完全被走訪過，至少需要遍歷幾個 `arr` 中的 element？回傳 `arr` 中第一個完全走訪過 `mat` 的某一行或某一列的 element 的 index。

## 解題思路

### 1. Hash Map

我們可以創建兩個大小分別是 `m` 和 `n` 的陣列 `row` 和 `col` 用於紀錄每行每列當前有幾個 element 已經被走訪過，`row[i]` 表示第 `i` 列有幾個 element 被走訪過，`col[i]` 表示第 `i` 行有幾個 element 被走訪過，然後創建一個陣列 `pos`，`pos[i]` 表示整數 `i` 在 `mat` 中的 index，接著遍歷 `arr`，依序將 `arr[i]` 對應的 `row` 和 `col` 的值 + 1，如果 $row[i] = n$ 或 $col[i] = m$ 表示這一行或這一列已經完全被走訪過，return `i`。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    int firstCompleteIndex(std::vector<int> &arr, std::vector<std::vector<int>> &mat) {
        int r = mat.size(), c = mat[0].size();
        // row 和 col 用於記錄每行每列有幾個 element 被走訪過
        int row[r], col[c];
        std::memset(row, 0, sizeof(row));
        std::memset(col, 0, sizeof(col));
        // pos[i] 表示 i 在 mat 中的 index
        int pos[r * c + 1];
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                int n = mat[i][j];
                pos[n] = i * c + j;
            }
        }

        // 遍歷 arr，將遇到的 element 所對應的 row 和 col 的值 - 1
        for (int i = 0; i < arr.size(); ++i) {
            int x = pos[arr[i]] / c, y = pos[arr[i]] % c;
            ++row[x], ++col[y];
            if (row[x] == c || col[y] == r) {
                return i;
            }
        }

        return -1;
    }
};
```

[![](https://i.imgur.com/1rJcEmi.png)](https://i.imgur.com/1rJcEmi.png)

#### 複雜度分析

令 $m$ 和 $n$ 分別為 `mat` 的列數和行數

- 時間複雜度： $O(m \cdot n)$

- 空間複雜度： $O(m \cdot n)$
