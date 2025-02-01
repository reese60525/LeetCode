# <center> [1267. Count Servers that Communicate](https://leetcode.com/problems/count-servers-that-communicate/description/) </center>

## 題目敘述

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501231844211.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501231844211.png)

給一個 $m \times n$ 的二維整數陣列 `grid` 表示伺服器的分布狀況，若 $grid[i][j] = 1$ 表示在 (i, j) 有一台伺服器，反之則沒有。

對於兩台伺服器若位於同一列或同一行則表示可以相連通，請算出共有幾台伺服器可以和別的伺服器連通。

## 解題思路

### 1. Hash Table

令 `row` 和 `col` 分別是在 `grid` 中每一列和每一行的伺服器數量，遍歷 `grid` 計算出 `row` 和 `col`，接著再遍歷一次 `grid`，如果當前 $grid[i][j] = 1$ 且 $row[i] > 1$ 或是 $col[j] > 1$ 表示當前位置的伺服器在當前行或列有別的伺服器可以連通，將答案 + 1，遍歷完後即可算出答案。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    int countServers(std::vector<std::vector<int>> &grid) {
        int m = grid.size(), n = grid[0].size();
        int row[m], col[n];
        std::memset(row, 0, sizeof(row));
        std::memset(col, 0, sizeof(col));

        // 計算每一行每一列的伺服器數量
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                row[i] += grid[i][j];
                col[j] += grid[i][j];
            }
        }

        // 計算共有幾台伺服器可以和別的伺服器連通
        int res = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                res += (grid[i][j] && (row[i] > 1 || col[j] > 1));
            }
        }

        return res;
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501231852238.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501231852238.png)

#### 複雜度分析

令 $m$ 和 $n$ 分別為 `grid` 的列數和行數。

- 時間複雜度： $O(m \cdot n)$

- 空間複雜度： $O(m + n)$
