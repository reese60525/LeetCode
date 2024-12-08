# <center> [LeetCode - 322. Coin Change](https://leetcode.com/problems/coin-change/description/) </center>

## 題目敘述

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241206194949537.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241206194949537.png)

給一個 integer array `coins` 和一個 integer `amount`，`coins` 中的所有硬幣都能使用無限次，請找到湊出 `amount` 所需的最少硬幣數量。若無法湊出，則 return -1。

e.g.

1. `coins` = {1, 2, 5}，`amount` = 11
    可以找到一組解 {1, 1, 5} 花費最少硬幣，因此答案為 3。

2. `coins` = {2}，`amount` = 3
    無法湊出 3，因此答案為 -1。

該題目中的 `coins` 的 element 可以無限使用，因此可以這是一個完全背包問題。

## 解題思路

### 1. Backtracking Algorithm

對於每個 `coins[i]`，有兩種選擇，分別為使用 `coins[i]` 和 不使用 `coins[i]`，因此可以將每個 `coins[i]` 當作一個節點，並且將每個節點的兩個子節點分別為使用 `coins[i]` 和 不使用 `coins[i]`，最後將所有可能的路徑加總起來，即可得到答案。

遞迴公式:

$$
f(i, sum) =
    \begin{cases}
        0 & \text{if } i < 0\ \ \&\ sum = 0 \\
        \infty & \text{if } i < 0\ \ \&\  sum < 0 \\
        f(i - 1, sum)& \text{if } sum < coins[i] \\
        \min(f(i - 1, sum), f(i, sum - coins[i]) + 1) & \text{otherwise}
    \end{cases}
$$

`i` 是 `coins` 的 index，如果 $i = 0$ 分成兩種情況，一個是 $sum = 0$，另一個是 $sum < 0$，前者代表已經湊出總額，後者代表湊不出總額，分別 return 0 和 無窮大。  
如果 $i > 0$ 分成兩種情況，一個是 $sum < coins[i]$，另一個是 $sum \geq coins[i]$，前者代表當前硬幣面額大於總額，因此無法使用該硬幣，後者代表當前硬幣面額小於等於總額，因此可以選擇使用該硬幣或是不使用該硬幣，並且取兩者中使用硬幣數較少者。如果使用了硬幣 `coins[i]`，則 `sum` 要減去 `coins[i]`，並且 `i` 不變，因為硬幣可以無限取用。

#### 程式碼

```c++ {.line-numbers}
class Solution {
  public:
    int dfs(std::vector<int> &coins, int index, int sum) {
        // 遍歷完所有硬幣，檢查是否湊出總額
        if (index < 0) {
            // 如果沒湊出總額，則返回一個無窮大的數，表示無解
            return sum == 0 ? 0 : 0x3f3f3f;
        }

        /// 如果當前硬幣面值大於總額，則跳過該硬幣
        if (sum < coins[index]) {
            return dfs(coins, index - 1, sum);
        }
        else {
            // 將選和不選該硬幣進行比較，取使用硬幣數較少的
            // 要注意的是由於硬幣能無限取用，因此選則用該硬幣的 dfs 的 index
            // 不變
            return std::min(dfs(coins, index - 1, sum), dfs(coins, index, sum - coins[index]) + 1);
        }
    }

    int coinChange(std::vector<int> &coins, int amount) {
        int res = dfs(coins, coins.size() - 1, amount);

        // 如果結果為無窮大，則表示無解，返回 -1
        return res == 0x3f3f3f ? -1 : res;
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241206202646766.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241206202646766.png)

時間複雜度: $O(2^{n+m})$，其中 $n$ 為 `coins` 的大小， $m$ 為 `amount`。***(不確定)***  
空間複雜度: $O(m)$

### 2. Dynamic Programming

#### 將遞迴轉換成動態規劃(DP)

##### DP 初始值

在遞迴寫法中的邊界條件為:

```c++ {.line-numbers}
if (index < 0) {
    return sum == 0 ? 0 : 0x3f3f3f;
}
```

將 `dp` 的大小設為 `dp[coins.size() + 1][amount + 1]`，`coins.size() + 1` 多出來的 **1** 是為了處理邊界條件中 `index` 為 **-1** 的情況，防止 `index` out of range，而 `amount + 1` 是因為 `amount` 的範圍為 **[0, amount]** 共 **amount + 1** 種情況。  
根據遞迴中的邊界條件，可以將 `dp` 的初始值設為 `dp[0][0] = 0`，表示當 `index` 為 **-1** 且 `sum` 為 **0** 時，使用硬幣數為 **0**，而其他位置則初始化為無窮大。

##### DP 狀態轉移公式

根據遞迴公式，可以將 `dp` 的狀態轉移公式設為:

$$
dp[i, sum] =
    \begin{cases}
        dp[i - 1][sum]& \text{if } sum < coins[i] \\
        \min(dp[i - 1][sum], dp[i][sum - coins[i]] + 1) & \text{otherwise}
    \end{cases}
$$

```c++ {.line-numbers}
if (j < coins[i]) {
    dp[i + 1][j] = dp[i][j];
}
else {
    dp[i + 1][j] = std::min(dp[i][j], dp[i + 1][j - coins[i]] + 1);
}
```

特別注意 `dp[i + 1][j - coins[i]] + 1`，由於硬幣能無限用，其 row index 要為 **i + 1**，也就是使用該硬幣之前和之後的 `index` 保持不變。

##### 程式碼

```c++ {.line-numbers}
class Solution {
  public:
    int coinChange(std::vector<int> &coins, int amount) {
        // dp[i][j] 表示前 i 個硬幣湊成金額 j 的最少硬幣數量
        std::vector<std::vector<int>> dp(coins.size() + 1, std::vector<int>(amount + 1, 0x3f3f3f));
        dp[0][0] = 0;

        for (int i = 0; i < coins.size(); ++i) {
            for (int j = 0; j <= amount; ++j) {
                if (j < coins[i]) {
                    dp[i + 1][j] = dp[i][j];
                }
                else {
                    // 特別注意 dp[i + 1][j - coins[i]] + 1，
                    // 由於硬幣能無限用，其 row index 要為 i + 1
                    dp[i + 1][j] = std::min(dp[i][j], dp[i + 1][j - coins[i]] + 1);
                }
            }
        }

        // 如果結果為無窮大，則表示無解，return -1
        return dp[coins.size()][amount] == 0x3f3f3f ? -1 : dp[coins.size()][amount];
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241207175214290.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241207175214290.png)

時間複雜度: $O(nm)$，其中 $n$ 為 `coins` 的大小，$m$ 為 `amount`。  
空間複雜度: $O(nm)$

#### DP 空間優化

**在 LeetCode-494 這道題目中已經有詳細分析如何將 DP 空間優化，這裡就不再贅述。**

需要注意的點是，LeetCode-494 中最終將 `dp` 的空間優化成一維陣列，其 `dp[i]` 是從最後面開始往前面計算的。  
而在這個題目， dp 狀態轉移公式是長這樣的:  

$$
dp[i, sum] =
    \begin{cases}
        dp[i - 1][sum]& \text{if } sum < coins[i] \\
        \min(dp[i - 1][sum], dp[i][sum - coins[i]] + 1) & \text{otherwise}
    \end{cases}
$$

**需要特別注意 `dp[i, sum - coins[i]] + 1`**，`dp[i]` 的狀態是由 **原本的 `dp[i-1]`** 和 **更新後的 `dp[i]`** 來計算的，因此 `dp[i]` 要由最前面開始往後計算才對。

假設現在的 `dp[]` 只有一維，`dp[i]` 和 `dp[i+1]` **都使用同個陣列**，當 $coins[i] = 2$時，有以下 dp 狀態，依序填入 `dp[i+1]` 的值

| dp[]    | dp[][0] | dp[][1] | dp[][2] | dp[][3] | dp[][4] | dp[][4] | dp[][5] |
| ------- | :-----: | :-----: | :-----: | :-----: | :-----: | :-----: | :-----: |
| dp[i]   |    1    |    2    |    3    |    4    |    5    |    6    |    7    |
| dp[i+1] |    -    |    -    |    -    |    -    |    -    |    -    |    -    |

`dp[i+1][0]` 和 `dp[i+1][1]` 因為 $j < coins[i]$，所以狀態不改變。

| dp[]    | dp[][0] | dp[][1] | dp[][2] | dp[][3] | dp[][4] | dp[][4] | dp[][5] |
| ------- | :-----: | :-----: | :-----: | :-----: | :-----: | :-----: | :-----: |
| dp[i]   |    1    |    2    |    3    |    4    |    5    |    6    |    7    |
| dp[i+1] |    1    |    2    |    -    |    -    |    -    |    -    |    -    |

`dp[i+1][2]` 由 $min(dp[i][2], dp[i+1][0] + 1)$ 得到 $dp[i][2] = 3$ ， $dp[i+1][0] + 1 = 2$ ，所以 $dp[i+1][2] = 2$ 。

| dp[]    | dp[][0] | dp[][1] | dp[][2] | dp[][3] | dp[][4] | dp[][4] | dp[][5] |
| ------- | :-----: | :-----: | :-----: | :-----: | :-----: | :-----: | :-----: |
| dp[i]   |    1    |    2    |    3    |    4    |    5    |    6    |    7    |
| dp[i+1] |    1    |    2    |    2    |    -    |    -    |    -    |    -    |

`dp[i+1][3]` 由 $min(dp[i][3], dp[i+1][1] + 1)$ 得到 $dp[i][3]= 4$ ， $dp[i+1][1] + 1 = 3$ ，所以 $dp[i+1][3] = 3$ 。

| dp[]    | dp[][0] | dp[][1] | dp[][2] | dp[][3] | dp[][4] | dp[][4] | dp[][5] |
| ------- | :-----: | :-----: | :-----: | :-----: | :-----: | :-----: | :-----: |
| dp[i]   |    1    |    2    |    3    |    4    |    5    |    6    |    7    |
| dp[i+1] |    1    |    2    |    2    |    3    |    -    |    -    |    -    |

**接下來是重點**
`dp[i+1][4]` 由 $min(dp[i][4], dp[i+1][2] + 1)$ 得到，雖然 `dp[i+1][2]` 的值已經被 `dp[i+1][0] + 1` 覆蓋，從原本的 $3$ 變成 $2$，但從 dp 轉移公式來看就是需要 $dp[i+1][] + 1$ 而不是 $dp[i][] + 1$ ，所以 `dp[][2]` 這個位置的值就該是 `dp[i+1][2]` 而不是舊的 `dp[i][2]`，因此要從前面往後開始計算才能確保得到的 `dp[i+1][]` 是正確的值。

| dp[]    | dp[][0] | dp[][1] | dp[][2] | dp[][3] | dp[][4] | dp[][4] | dp[][5] |
| ------- | :-----: | :-----: | :-----: | :-----: | :-----: | :-----: | :-----: |
| dp[i]   |    1    |    2    |    3    |    4    |    5    |    6    |    7    |
| dp[i+1] |    1    |    2    |    4    |    6    |    3    |    -    |    -    |

最後，DP 轉移公式從:

$$
dp[i, sum] =
    \begin{cases}
        dp[i - 1][sum]& \text{if } sum < coins[i] \\
        \min(dp[i - 1][sum], dp[i][sum - coins[i]] + 1) & \text{otherwise}
    \end{cases}
$$

被簡化成:

$$
dp[sum] = \min(dp[sum], dp[sum - coins[i]] + 1)
$$

```c++ {.line-numbers}
// 原本二維的 dp 狀態轉移公式
for (int i = 0; i < coins.size(); ++i) {
    for (int j = 0; j <= amount; ++j) {
        if (j < coins[i]) {
            dp[i + 1][j] = dp[i][j];
        }
        else {
            dp[i + 1][j] = std::min(dp[i][j], dp[i + 1][j - coins[i]] + 1);
        }
    }
}

// 簡化成一維的 dp 狀態轉移公式
// 1. 先刪除所有 row
for (int i = 0; i < coins.size(); ++i) {
    for (int j = 0; j <= amount; ++j) {
        if (j < coins[i]) {
            dp[j] = dp[j];
        }
        else {
            dp[j] = std::min(dp[j], dp[j - coins[i]] + 1);
        }
    }
}

// 2. 在 if (j < coins[i]) 中 dp[j] 的值不會改變，所以可以省略
//    把 j 的迴圈從 coins[i] 開始，因為 coins[i] 之前的 dp[j] 值不會改變
for (int i = 0; i < coins.size(); ++i) {
    for (int j = coins[i]; j <= amount; ++j) {
        dp[j] = std::min(dp[j], dp[j - coins[i]] + 1);
    }
}
```

##### 程式碼

```c++ {.line-numbers}
class Solution {
  public:
    int coinChange(std::vector<int> &coins, int amount) {
        std::vector<int> dp(amount + 1, 0x3f3f3f);
        dp[0] = 0;

        for (int i = 0; i < coins.size(); ++i) {
            for (int j = coins[i]; j <= amount; ++j) {
                dp[j] = std::min(dp[j], dp[j - coins[i]] + 1);
            }
        }

        // 如果結果為無窮大，則表示無解，return -1
        return dp[amount] == 0x3f3f3f ? -1 : dp[amount];
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241206214453302.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241206214453302.png)

時間複雜度: $O(nm)$，其中 $n$ 為 `coins` 的大小，$m$ 為 `amount`。  
空間複雜度: $O(m)$
