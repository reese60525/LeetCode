# <center> [518. Coin Change II](https://leetcode.com/problems/coin-change-ii/description/) </center>

## 題目敘述

[![](https://i.imgur.com/pxvPND4.png)](https://i.imgur.com/pxvPND4.png)

給一組整數陣列 `coins` 和整數 `amount`，分別代表硬幣的種類和要湊齊的總金額，每種硬幣都可以**無限取用**，找出所有能湊出 `amount` 的組合數量。

## 解題思路

### 1. Dynamic Programming（DP）

這題和 [322. Coin Change](https://github.com/reese60525/LeetCode/blob/main/Leetcode/LeetCode-322/Solution-322.md#2-dynamic-programming) 是相似題，差別在於這題是求組合數量，而不是求最小硬幣數量。

令 `i` 為 `coins` 的 index，`i` 從 $n-1$ 開始，`j` 為目前剩餘的總金額，根據題目要求，我們可以寫出以下遞迴 code：

```cpp {.line-numbers}
// 用於幫助理解從 dfs 轉為 dp 的 code
int dfs(int sum, int idx, const std::vector<int> &coins) {
    if (idx < 0) {
        return sum == 0;
    }

    if (coins[idx] > sum) {
        return dfs(sum, idx - 1, coins);
    }
    return dfs(sum, idx - 1, coins) + dfs(sum - coins[idx], idx, coins);
}
```

遞迴關係式：

$$
dfs(i,j) = \begin{cases}
1 & i = -1 \text{ and }  j = 0 \\
0 & i = -1 \text{ and } j \neq 0 \\
dfs(i-1,j) & j < coins[i] \\
dfs(i-1,j) + dfs(i,j-coins[i]) & j \geq coins[i] \\
\end{cases}
$$

定義一個二維整數陣列 `dp`，其中 `dp[i][j]` 表示使用前 `i` 種硬幣湊出金額 `j` 的組合數量。可以將以上遞迴關係式轉換成以下 DP 狀態轉移公式：

$$
dp[i+1][j] = \begin{cases}
1 & i = 0 \text{ and }  j = 0 \\
0 & i = 0 \text{ and } j \neq 0 \\
dp[i][j] & j < coins[i] \\
dp[i][j] + dp[i+1][j-coins[i]] & j \geq coins[i] \\
\end{cases}
$$

由於 `dp[i+1][j]` 只與 `dp[i][j]` 和 `dp[i+1][j-coins[i]]` 有關，因此可以將二維陣列 `dp[i][j]` 壓縮成一維陣列 `dp[j]`。

#### 程式碼

二維 `dp` 版本：

```cpp {.line-numbers}
class Solution {
  public:
    int change(int amount, std::vector<int> &coins) {
        // 需要用 unsigned long long 才能過測資
        unsigned long long dp[coins.size() + 1][amount + 1];
        std::memset(dp, 0, sizeof(dp));
        dp[0][0] = 1;

        for (size_t i = 0; i < coins.size(); ++i) {
            for (size_t j = 0; j <= amount; ++j) {
                if (coins[i] > j) {
                    dp[i + 1][j] = dp[i][j];
                }
                else {
                    dp[i + 1][j] = dp[i][j] + dp[i + 1][j - coins[i]];
                }
            }
        }

        return dp[coins.size()][amount];
    }
};
```

一維 `dp` 版本：

```cpp {.line-numbers}
class Solution {
  public:
    int change(int amount, std::vector<int> &coins) {
        // 需要用 unsigned long long 才能過測資
        unsigned long long dp[amount + 1];
        std::memset(dp, 0, sizeof(dp));
        dp[0] = 1;

        for (size_t i = 0; i < coins.size(); ++i) {
            for (size_t j = 0; j <= amount; ++j) {
                if (coins[i] > j) {
                    dp[j] = dp[j];
                }
                else {
                    dp[j] = dp[j] + dp[j - coins[i]];
                }
            }
        }

        return dp[amount];
    }
};
```

最後，進一步簡化 `dp` 處理邏輯：

```cpp {.line-numbers}
class Solution {
  public:
    int change(int amount, std::vector<int> &coins) {
        // 需要用 unsigned long long 才能過測資
        unsigned long long dp[amount + 1];
        std::memset(dp, 0, sizeof(dp));
        dp[0] = 1;

        for (size_t i = 0; i < coins.size(); ++i) {
            for (size_t j = coins[i]; j <= amount; ++j) {
                dp[j] += dp[j - coins[i]];
            }
        }

        return dp[amount];
    }
};
```

[![](https://i.imgur.com/bnlX52P.png)](https://i.imgur.com/bnlX52P.png)

#### 複雜度分析

令 $n$ 為硬幣的種類數量， $amount$ 為要湊齊的總金額。

- 時間複雜度： $O(n \cdot amount)$

- 空間複雜度： $O(amount)$
