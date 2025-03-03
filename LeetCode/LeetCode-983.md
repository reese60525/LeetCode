# <center> [983. Minimum Cost For Tickets](https://leetcode.com/problems/minimum-cost-for-tickets/description/) </center>

## 題目敘述

[![](https://i.imgur.com/0ePgFDi.png)](https://i.imgur.com/0ePgFDi.png)

給一個整數陣列 `days` 代表要旅遊的日期，以及一個大小為 3 的整數陣列 `costs` 代表三種票價，`costs[0]` 到 `costs[3]` 分別代表 1、7、30 天的票價，請計算出完成每一天旅遊的最小車票成本。

## 解題思路

### 1. Dynamic Programming

經典的無限背包問題，令 `n` 為 `days` 的長度，從旅遊的最後一天 `days[n-1]` 開始選車票，假如我選了 7 天的票，那麼 `[day[n-1] - 6, days[n-1]]` 這段區間都有車票了，如果 `days[n-2]` 在這個區間的話就不用再買車票，直接跳過，`day[n-3]` 也是一樣的概念，以此類推，直到 `days[k]` 不在這區間內才要再買車票。

將以上想法寫成 DFS code 如下：

```cpp {.line-numbers}
class Solution {
  private:
    std::vector<int> days;
    std::vector<int> costs;

  public:
    int dfs(int idx) {
        // 如果所有 day 都買車票了就結束遞迴
        if (idx < 0) {
            return 0;
        }

        // 略過已經有買車票的 day
        int idx7 = idx, idx30 = idx;
        while (--idx7 >= 0 && days[idx] - days[idx7] < 7) {}
        while (--idx30 >= 0 && days[idx] - days[idx30] < 30) {}

        return std::min({dfs(idx - 1) + costs[0], dfs(idx7) + costs[1], dfs(idx30) + costs[2]});
    }

    int mincostTickets(std::vector<int> &days, std::vector<int> &costs) {
        this->days = days;
        this->costs = costs;

        return dfs(days.size() - 1);
    }
};
```

令 `dp[i]` 表示前 `i` 個旅遊日所需的最小成本，而第 `i` 個旅遊日在 `days` 為 `days[i-1]`，如果我在第 `i` 個旅遊選擇買了 7 天的票，那麼 `[days[i-1] - 6, days[i-1]]` 都是有車票的，找到一個最大的 `j` 使得 $days[j] < days[i-1] - 6$ ，那麼買 7 天票的最小成本 $dp[i]_7 = dp[j] + costs[1]$ ，而 `j` 的範圍是 $0 \leq j < i$ 。計算所有在第 `i` 個旅遊日買的三種票的花費，取最小值就能得到 `dp[i]`，最後 `dp[n]` 就是答案。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    int mincostTickets(std::vector<int> &days, std::vector<int> &costs) {
        // dp[k] 表示前 k 個旅遊日所需要的最小車票花費
        int dp[days.size() + 1];
        dp[0] = 0;

        for (int i = 1; i <= days.size(); ++i) {
            // 前 i 個旅遊在 days 中的 index 要變成 i - 1
            // 例如：前 4 個旅遊在 days 中的 index 為 {0, 1, 2, 3}
            // 這步驟是要將已經買了目前的車票的旅遊日略過
            int idx7 = i - 1, idx30 = i - 1;
            while (--idx7 >= 0 && days[i - 1] - days[idx7] < 7) {}
            while (--idx30 >= 0 && days[i - 1] - days[idx30] < 30) {}
            // 因為 dp[k] 的 k 是指第 k 個旅遊日，所以要把 days index 再 + 1
            dp[i] = std::min({dp[i - 1] + costs[0], dp[idx7 + 1] + costs[1], dp[idx30 + 1] + costs[2]});
        }

        return dp[days.size()];
    }
};
```

[![](https://i.imgur.com/wvHrLes.png)](https://i.imgur.com/wvHrLes.png)

#### 複雜度分析

令 $n$ 為 `days` 的長度。

- 時間複雜度： $O(n)$

- 空間複雜度： $O(n)$
