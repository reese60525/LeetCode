# <center> [1937. Maximum Number of Points with Cost](https://leetcode.com/problems/maximum-number-of-points-with-cost/description/) </center>

## 題目敘述

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241227155639613.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241227155639613.png)

給一個大小為 $m \times n$ 的整數矩陣 `points`，對於每一個 row 都能選一個 element，且相鄰 row 選中的 element 如果在不同 column，則會有個 `cost`，例如選了 `points[2][5]` 和 `points[3][2]`，則 $cost = abs(j_{row2} - j_{row3}) = abs(5 - 2) = 3$ ，求將所有選中的 element 相加並減去所有 cost 後的最大值。

## 解題思路

### 1. Dynamic Programming

創建一個 2D integer array `dp[i]][j]` 表示如果選了 `points[i][j]` 時最大值，而 `dp[i][j]` 是當前 `point[i][j]` 和 `max(dp[i-1][k] - cost)` 相加得來，因此可得到以下狀態轉移公式：  

$$
dp[i][j] = max(dp[i-1][k] - abs(j - k)) + points[i][j]
$$

這樣的時間複雜度會是 $O(m \cdot n^2)$ ，因為 `dp` 為 $m \cdot n$ 大小並且每個 `dp[i][j]` 都要遍歷 `dp[i-1]` 的所有element，因此需要優化。  

將 `dp[i][j]` 的狀態轉移公式中的絕對值拆解成兩部分：

$$
dp[i][j] =
\begin{cases}
max(dp[i-1][k] - (j - k)) + points[i][j] & \text{if } j \geq k \\
max(dp[i-1][k] - (k - j)) + points[i][j] & \text{if } j \leq k \\
\end{cases}
$$

可以創建兩個 integer array `leftMax` 和 `rightMax` 分別表示在當前 `dp[i][j]` 時，在 `dp[i-1]` 中 `j` 左邊的總和減去到 `j` 的成本的最大值和右邊的總和減去到 `j` 的成本的最大值，因此狀態轉移公式就能簡化成：

$$
dp[i][j] = max(leftMax[j] + rightMax[j]) + points[i][j]
$$

動態維護 `leftMax` 和 `rightMax` 的時間複雜度為 $O(1)$ ，因此計算每個 `dp[i][j]` 的時間複雜度從 $O(n)$ 變成 $O(1)$ ，最終整體時間複雜度為 $O(m \cdot n)$ 。  

一些比較細節的部分，在初始化 `dp` 時，由於 `dp[0]` 沒有 `dp[i-1]` 可以參考，因此 `dp[0][j]` 的值就會是 `points[0][j]` 的值。  
而計算 `leftMax` 和 `rightMax` 時，`leftMax` 的範圍是 $[0, j]$ 、`rightMax` 的範圍是 $[j, n-1]$ ，雖然在 index = `j` 時有重複但不影響結果。由於計算 `dp[i][j]` 時是由左而右迭代，因此 `leftMax` 不需要創立為一個 array，只需要在迭代 `dp[i]` 的過程中和 `dp[i-1][j] - cost` 比較取較大值就能完成維護，`rightMax` 則需要創立一個 array 在迭代 `dp[i]` 前先計算好。

e.g.  

`points` =

```text
{{4, 4, 2, 2, 1},  
 {5, 5, 2, 1, 2},  
 {3, 1, 5, 5, 2},  
 {3, 2, 0, 0, 3}}  
 ```

- 首先初始化 `dp[0]` 為 `points[0]` 的值

    ```text
    dp[0] = {4, 4, 2, 2, 1}
    dp = 
    {{4, 4, 2, 2, 1},
     {0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0}}
    ```

- 接著從 `i` = 1 開始遍歷 `points` 的每一個 row，計算 `dp[i]` 的值。  
  - 在 `dp[1][0]` 時， $leftMax[0] = 4 - 0 = 4$ ， $rightMax[0] = 4 - 0 = 4$ ， $points[1][0] = 5$ ，因此 $dp[1][0] = max(4, 4) + 5 = 9$ 。
  - 在 `dp[1][1]` 時， $leftMax[1] = 4 - 0 = 4$ ， $rightMax[1] = 4 - 0 = 4$ ， $points[1][1] = 5$ ，因此 $dp[1][1] = max(4, 4) + 5 = 9$ 。
  - 在 `dp[1][2]` 時， $leftMax[2] = 4 - 1 = 3$ ， $rightMax[2] = 2 - 0 = 2$ ， $points[1][2] = 2$ ，因此 $dp[1][2] = max(3, 2) + 2 = 5$ 。
  - 在 `dp[1][3]` 時， $leftMax[3] = 4 - 2 = 2$ ， $rightMax[3] = 2 - 0 = 2$ ， $points[1][3] = 1$ ，因此 $dp[1][3] = max(2, 2) + 1 = 3$ 。
  - 在 `dp[1][4]` 時， $leftMax[4] = 4 - 3 = 1$ ， $rightMax[4] = 1 - 0 = 1$ ， $points[1][4] = 2$ ，因此 $dp[1][4] = max(1, 1) + 2 = 3$ 。
  - 最終：

    ```text
    dp[1] = {9, 9, 5, 3, 3}
    dp = 
    {{4, 4, 2, 2, 1},
     {9, 9, 5, 3, 3},
     {0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0}}
      ```

- `i` = 2 時。
  - 在 `dp[2][0]` 時， $leftMax[0] = 9 - 0 = 9$ ， $rightMax[0] = 9 - 0 = 9$ ， $points[2][0] = 3$ ，因此 $dp[2][0] = max(9, 9) + 3 = 12$ 。
  - 在 `dp[2][1]` 時， $leftMax[1] = 9 - 0 = 9$ ， $rightMax[1] = 9 - 0 = 9$ ， $points[2][1] = 1$ ，因此 $dp[2][1] = max(9, 9) + 1 = 10$ 。
  - 在 `dp[2][2]` 時， $leftMax[2] = 9 - 1 = 8$ ， $rightMax[2] = 5 - 0 = 5$ ， $points[2][2] = 5$ ，因此 $dp[2][2] = max(8, 5) + 5 = 13$ 。
  - 在 `dp[2][3]` 時， $leftMax[3] = 9 - 2 = 7$ ， $rightMax[3] = 3 - 0 = 3$ ， $points[2][3] = 5$ ，因此 $dp[2][3] = max(7, 3) + 5 = 12$ 。
  - 在 `dp[2][4]` 時， $leftMax[4] = 9 - 3 = 6$ ， $rightMax[4] = 3 - 0 = 3$ ， $points[2][4] = 2$ ，因此 $dp[2][4] = max(6, 3) + 2 = 8$ 。
  - 最終：

    ```text
    dp[1] = {12, 10, 13, 12, 8}
    dp = 
    {{4, 4, 2, 2, 1},
     {9, 9, 5, 3, 3},
     {12, 10, 13, 12, 8},
     {0, 0, 0, 0, 0}}
      ```

- `i` = 3 時。
  - 在 `dp[3][0]` 時， $leftMax[0] = 12 - 0 = 12$ ， $rightMax[0] = 12 - 0 = 12$ ， $points[3][0] = 3$ ，因此 $dp[3][0] = max(12, 12) + 3 = 15$ 。
  - 在 `dp[3][1]` 時， $leftMax[1] = 12 - 0 = 12$ ， $rightMax[1] = 12 - 0 = 12$ ， $points[3][1] = 2$ ，因此 $dp[3][1] = max(12, 12) + 2 = 14$ 。
  - 在 `dp[3][2]` 時， $leftMax[2] = 13 - 0 = 13$ ， $rightMax[2] = 13 - 0 = 13$ ， $points[3][2] = 0$ ，因此 $dp[3][2] = max(13, 13) + 0 = 13$ 。
  - 在 `dp[3][3]` 時， $leftMax[3] = 13 - 1 = 12$ ， $rightMax[3] = 12 - 0 = 12$ ， $points[3][3] = 0$ ，因此 $dp[3][3] = max(12, 12) + 0 = 12$ 。
  - 在 `dp[3][4]` 時， $leftMax[4] = 13 - 2 = 11$ ， $rightMax[4] = 8 - 0 = 8$ ， $points[3][4] = 3$ ，因此 $dp[3][4] = max(11, 8) + 3 = 14$ 。
  - 最終：

    ```text
    dp[1] = {15, 14, 13, 12, 14}
    dp = 
    {{4, 4, 2, 2, 1},
     {9, 9, 5, 3, 3},
     {12, 10, 13, 12, 8},
     {15, 14, 13, 12, 14}}
    ```

- 最後回傳 `dp[m-1]` 的最大值即可，在這例子中是 `dp[3][0]` = 15。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    long long maxPoints(std::vector<std::vector<int>> &points) {
        int m = points.size(), n = points[0].size();

        // 初始化 dp
        long long dp[m][n];
        for (int i = 0; i < n; ++i) {
            dp[0][i] = points[0][i];
        }

        // 迭代更新每一層 dp
        for (int i = 1; i < m; ++i) {
            // prefix max
            long long left_max = 0;
            // suffix max
            long long right_max[n];
            right_max[n - 1] = dp[i - 1][n - 1];
            for (long long j = n - 2; j >= 0; --j) {
                right_max[j] = std::max(right_max[j + 1] - 1, dp[i - 1][j]);
            }

            for (int j = 0; j < n; ++j) {
                // 更新 prefix max
                left_max = std::max(left_max - 1, dp[i - 1][j]);
                dp[i][j] = points[i][j] + std::max(left_max, right_max[j]);
            }
        }

        long long res = 0;
        for (int i = 0; i < n; ++i) {
            res = std::max(res, dp[m - 1][i]);
        }

        return res;
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241227184025150.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241227184025150.png)

時間複雜度： $O(m \cdot n)$ ，其中 $m$ 是 `points` 的 row 數， $n$ 是 `points` 的 column 數。  
空間複雜度： $O(m \cdot n)$ ，`dp` 矩陣的大小為 $m \times n$ 。

---
由於 `dp[i]` 只和 `dp[i-1]` 有關，因此可以將 `dp` 矩陣壓縮成一維陣列，空間複雜度可以降到 $O(n)$ ，直接刪除 `dp` 矩陣的第一維就好。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    long long maxPoints(std::vector<std::vector<int>> &points) {
        int m = points.size(), n = points[0].size();

        // 初始化 dp
        long long dp[n];
        for (int i = 0; i < n; ++i) {
            dp[i] = points[0][i];
        }

        // 迭代更新每一層 dp
        for (int i = 1; i < m; ++i) {
            // prefix max
            long long left_max = 0;
            // suffix max
            long long right_max[n];
            right_max[n - 1] = dp[n - 1];
            for (long long j = n - 2; j >= 0; --j) {
                right_max[j] = std::max(right_max[j + 1] - 1, dp[j]);
            }

            for (int j = 0; j < n; ++j) {
                left_max = std::max(left_max - 1, dp[j]); // 更新 prefix max
                dp[j] = points[i][j] + std::max(left_max, right_max[j]);
            }
        }

        long long res = 0;
        for (int i = 0; i < n; ++i) {
            res = std::max(res, dp[i]);
        }

        return res;
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241227184133347.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241227184133347.png)

時間複雜度： $O(m \cdot n)$ ，其中 $m$ 是 `points` 的 row 數， $n$ 是 `points` 的 column 數。  
空間複雜度： $O(n)$ ，`dp` 矩陣的大小為 $n$ 。
