# <center> [3264. Final Array State After K Multiplication Operations I](https://leetcode.com/problems/final-array-state-after-k-multiplication-operations-i/description/) </center>

# 题目描述

[![](https://i.imgur.com/FhLl8wy.png)](https://i.imgur.com/FhLl8wy.png)

給一個整數陣列 `nums`、整數 `k`、整數 `multiplier`，可以對 `nums` 做 `k` 次操作，每次操作對 `nums` 中最小值乘以 `multiplier`，若有數個相同的最小值則選擇 index 最小的。

e.g.

$nums = [1, 2, 3, 4, 5]$ ， $k = 4$ ， $multiplier = 2$

- 第一次操作：$nums = [2, 2, 3, 4, 5]$

- 第二次操作：$nums = [4, 2, 3, 4, 5]$

- 第三次操作：$nums = [4, 4, 3, 4, 5]$

- 第四次操作：$nums = [4, 4, 6, 4, 5]$

## 解題思路

### 1. Priority Queue

- 使用 priority queue 來維護 `nums` 的最小值，每次操作時將最小值乘以 `multiplier` 後再放回 priority queue 中。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    std::vector<int> getFinalState(std::vector<int> &nums, int k, int multiplier) {
        // 建立 min heap pq
        auto cmp = [&](size_t &a, size_t b) {
            return (nums[a] == nums[b]) ? a > b : nums[a] > nums[b];
        };
        std::priority_queue<size_t, std::vector<size_t>, decltype(cmp)> pq(cmp);
        for (size_t i = 0; i < nums.size(); ++i) {
            pq.push(i);
        }

        // 進行 k 次操作
        while (k--) {
            size_t idx = pq.top();
            pq.pop();
            nums[idx] *= multiplier;
            pq.push(idx);
        }

        return nums;
    }
};
```

[![](https://i.imgur.com/GRtKSZG.png)](https://i.imgur.com/GRtKSZG.png)

#### 複雜度分析

令 $n$ 為 `nums` 的長度， $k$ 為操作次數。

- 時間複雜度： $O((n + k) \log n)$

- 空間複雜度： $O(n)$
