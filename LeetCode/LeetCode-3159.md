# <center> [3159. Find Occurrences of an Element in an Array](https://leetcode.com/problems/find-occurrences-of-an-element-in-an-array/description/) </center>

## 題目敘述

[![](https://i.imgur.com/J1OAAwA.png)](https://i.imgur.com/J1OAAwA.png)

給一個整數 `x` 和兩個整數陣列 `nums` and `queries`，找出所有 `nums` 中第 `queries[i]` 個 `x` 的 index，若不存在則為 -1。

## 解題思路

### 1. Hash Map

將 `x` 第 `k` 出現的 index 存入一個 array 中，然後遍歷 `queries` 直接從該 array 取得答案即可。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    std::vector<int> occurrencesOfElement(std::vector<int> &nums, std::vector<int> &queries, int x) {
        size_t x_cnt = 0; // x_cnt 表示 x 出現次數
        for (size_t i = 0; i < nums.size(); ++i) {
            if (nums[i] == x) {
                nums[x_cnt] = i; // 直接覆蓋 nums 重複利用空間
                ++x_cnt;
            }
        }

        for (size_t i = 0; i < queries.size(); ++i) {
            // 由於 nums 是從 0 開始存，nums[0] 表示 x 第一次出現的 index
            // 所以查找 nums 時 queries[i] 要 -1
            queries[i] = queries[i] > x_cnt ? -1 : nums[queries[i] - 1];
        }

        return queries;
    }
};
```

[![](https://i.imgur.com/HfwTNpu.png)](https://i.imgur.com/HfwTNpu.png)

#### 複雜度分析

令 $n$ 為 `nums` 長度， $m$ 為 `queries` 長度。

- 時間複雜度： $O(n + m)$

- 空間複雜度： $O(1)$
