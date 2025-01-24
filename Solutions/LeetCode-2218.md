# <center> [2218. Maximum Value of K Coins From Piles](https://leetcode.com/problems/maximum-value-of-k-coins-from-piles/description/) </center>

## 題目敘述

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501221621048.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501221621048.png)

給一個二維整數陣列 `piles` 和整數 `k` 分別表示有數堆的硬幣 stack 和要從中取出的硬幣數量，`piles[i][j]` 代表第 `i` 堆硬幣中由 stack 頂部往下數的第 `j` 個硬幣，現在要從這些硬幣中選出 `k` 個硬幣，求出這些硬幣的總和最大值。

**每次從 stack 中取出硬幣必須是從 stack 頂部取出硬幣，不能從中間取。**

## 解題思路

### 1. Dynamic Programming and Prefix Sum

這題是 0-1 背包問題的變形，令 `i` 為剩餘尚未選取的硬幣堆數量，`j` 為剩餘要取出的硬幣數量，`n` 為當前硬幣堆的硬幣數量，則每個硬幣堆會有 `0 ~ min(n, j)` 種取法，將其寫成 DFS 的遞迴程式碼如下所示：

```cpp {.line-numbers}
class Solution {
  public:
    std::vector<std::vector<int>> piles;

    int dfs(int i, int j) {
        // 若沒有硬幣堆能取硬幣或剩餘要取出的硬幣數量為 0，則 return 0 表示結束遞迴
        if (i <= 0 || j == 0) {
            return 0;
        }

        int n = piles[i - 1].size(); // 當前硬幣堆的大小
        // 計算當前硬幣堆的 prefix sum，prefix_sum[l] 表示該硬幣堆取前 l 個硬幣的總和
        std::vector<int> prefix_sum(n + 1, 0);
        for (int l = 1; l <= n; ++l) {
            prefix_sum[l] = prefix_sum[l - 1] + piles[i - 1][l - 1];
        }
        // 根據 n 和 j 的大小來決定在當前硬幣堆能取出的硬幣數量，可以取 0 ~ min(n, j) 個硬幣
        // 當前硬幣堆有取出 0 ~ min(n, j) 個硬幣共 min(n, j) 種組合，將每個組合都進行 DFS 取最大值
        int max_val = 0;
        for (int l = 0; l <= std::min(n, j); ++l) {
            max_val = std::max(max_val, prefix_sum[l] + dfs(i - 1, j - l));
        }

        return max_val;
    }

    int maxValueOfCoins(std::vector<std::vector<int>> &piles, int k) {
        this->piles = piles;
        return dfs(piles.size(), k);
    }
};
```

將上述程式碼改成 DP，令 `dp[i][j]` 表示 前 `i` 個硬幣堆中選 `j` 個硬幣所能得到的最大總額，`n` 表示當前硬幣堆的硬幣數量，則狀態轉移方程式為：

$$
dp[i][j] =
\begin{cases}
0 & i \leq 0 \text{ or } j = 0 \\
\max\limits_{0 \le l \le \min(n, j)} \left( dp[i - 1][j - l] + \sum_{x = 0}^{l} piles[i-1][x] \right) & \text{otherwise } \\
\end{cases}
$$

確認好狀態轉移方程式後，就可以開始寫 DP 的程式碼了。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    int maxValueOfCoins(std::vector<std::vector<int>> &piles, int k) {
        int m = piles.size(); // 硬幣堆的數量
        int dp[m + 1][k + 1]; // dp[i][j] 表示前 i 堆硬幣堆中選取 j 個硬幣的最大價值
        std::memset(dp, 0, sizeof(dp));

        for (int i = 1; i <= m; ++i) {
            int n = piles[i - 1].size(); // 當前硬幣堆的硬幣數量
            // 計算當前硬幣堆的前綴合
            for (int j = 1; j < n; ++j) {
                piles[i - 1][j] += piles[i - 1][j - 1];
            }

            for (int j = 0; j <= k; ++j) {
                // 不選擇當前硬幣堆
                dp[i][j] = dp[i - 1][j];
                // 選擇當前硬幣堆前 1 ~ min(j, n) 個硬幣
                // 由於將選取 0 個硬幣的情況提出來了，所以是 dp[i-1][j-l-1] 而不是 dp[i-1][j-l]
                for (int l = 0; l < std::min(j, n); ++l) {
                    dp[i][j] = std::max(dp[i][j], dp[i - 1][j - l - 1] + piles[i - 1][l]);
                }
            }
        }

        return dp[m][k];
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501222035776.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501222035776.png)

#### 複雜度分析

令 $m$ 為硬幣堆的數量， $k$ 為要取出的硬幣數量， $l$ 為所有硬幣堆中平均硬幣數量， $M$ 為所有硬幣的數量。

- 時間複雜度： $O(M^2)$

    根據題目給的測資限制： $1 \leq k \leq sum(piles[i].length) \leq 2000$ ，也就是 $1 \leq k \leq M \leq 2000$ ，原本程式碼計算 `dp` 的時間複雜度為 $O(m \cdot k \cdot l)$ ，而 $m \cdot l = M$ ， $k$ 最壞情況下可以和 $M$ 一樣大，因此最終的時間複雜度為 $O(M^2)$ ， $M$ 最大為 2000。

- 空間複雜度： $O(m \cdot k)$

---

要進一步優化 DP 算法，可以發現 `dp[i][j]` 只和 `dp[i - 1][]` 有關，因此可以將 `dp` 壓縮成一維陣列，由於需要用到 `dp[][j - l - 1]`，所以要從後往前更新 `dp`，而不選擇當前硬幣堆的情況： `dp[i][j]` = `dp[i - 1][j]` 變成 `dp[j]` = `dp[j]`，可以直接省略。

接著考慮到前 `i` 個硬幣堆中共有 `x` 個硬幣，要是 `k` 大於 `x` 時有必要從 `k` 開始往前更新 `dp` 嗎？答案是不用的，因為當前最多就只能取出 `x` 個硬幣，因此可以用一個變數 `x` 來記錄前 `i` 個硬幣堆中共有多少個硬幣，在更新 `dp` 時 `j` 只要從 `min(x, k)` 開始往前更新就好。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    int maxValueOfCoins(std::vector<std::vector<int>> &piles, int k) {
        int m = piles.size(); // 硬幣堆的數量
        int x = 0;            // 紀錄前 i 個硬幣堆的硬幣總數
        int dp[k + 1];
        std::memset(dp, 0, sizeof(dp));

        for (int i = 1; i <= m; ++i) {
            int n = piles[i - 1].size(); // 當前硬幣堆的硬幣數量
            x += n;                      // 更新前 i 個硬幣堆的硬幣總數
            // 計算當前硬幣堆的前綴合，用 stl 計算前綴合速度效率會比較慢
            // partial_sum(piles[i - 1].begin(), piles[i - 1].end(), piles[i - 1].begin());
            for (int j = 1; j < n; ++j) {
                piles[i - 1][j] += piles[i - 1][j - 1];
            }
            //  若 k 大於前 i 個硬幣堆的硬幣總數 x，則只需要從 x 開始更新
            for (int j = std::min(x, k); j >= 0; --j) {
                for (int l = 0; l < std::min(j, n); ++l) {
                    dp[j] = std::max(dp[j], dp[j - l - 1] + piles[i - 1][l]);
                }
            }
        }

        return dp[k];
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501221858820.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501221858820.png)

#### 複雜度分析

令 $m$ 為硬幣堆的數量， $k$ 為要取出的硬幣數量， $l$ 為所有硬幣堆中平均硬幣數量， $M$ 為所有硬幣的數量。

- 時間複雜度： $O(M^2)$

- 空間複雜度： $O(k)$
