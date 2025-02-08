# <center> [2270. Number of Ways to Split Array](https://leetcode.com/problems/number-of-ways-to-split-array/description/) </center>

## 題目敘述

[![](https://i.imgur.com/mAGK57l.png)](https://i.imgur.com/mAGK57l.png)

給一個大小為 `n` 的整數陣列 `nums`，將其從 index `i` 切成兩邊，如果符合以下條件則為有效切割：

1. $\displaystyle \sum_{x = 0}^{i} num[x] \geq \displaystyle \sum_{x = i+1}^{n-1} num[x]$ 。

2. 左右兩邊不為空。

請回傳共有幾種有效切割方式。

## 解題思路

### 1. Prefix Sum

先計算出 `nums` 的總和 `total`，並用 `cur` 累加計算左邊的總和，右邊的總和就會是 $total - cur$ ，將左右兩邊比較大小即可判斷是否為有效切割。

**需要注意看題目測資範圍，`total` 會超過整數範圍**

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    int waysToSplitArray(std::vector<int> &nums) {
        // total 會超出整數範圍，init 要用 0LL 表示 long long type 的 0
        long long total = std::accumulate(nums.begin(), nums.end(), 0LL);
        long long cur = 0;
        int res = 0;
        for (size_t i = 0; i < nums.size() - 1; ++i) {
            cur += nums[i];
            res += cur >= (total - cur);
        }

        return res;
    }
};
```

[![](https://i.imgur.com/jm3uKRy.png)](https://i.imgur.com/jm3uKRy.png)

#### 複雜度分析

令 $n$ 為 `nums` 的長度。

- 時間複雜度： $O(n)$

- 空間複雜度： $O(1)$
