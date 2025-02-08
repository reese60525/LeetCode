# <center> [LeetCode - 2779. Maximum Beauty of an Array After Applying Operation](https://leetcode.com/problems/maximum-beauty-of-an-array-after-applying-operation/description/) </center>

## 題目敘述

[![](https://i.imgur.com/hBqvu1m.png)](https://i.imgur.com/hBqvu1m.png)

給一個整數陣列 `nums` 和一個整數 `k`，可以對 `nums` 做以下操作：

- 選擇一個 index `i`，將 $nums[i] = nums[i] + x$ ， $-k \leq x \leq k$ 。

- 每個 `nums[i]` 最多只能被操作一次。

求經過操作後 `nums` 所能形成的 `beauty subsequence` 的最大長度。

`beauty subsequence` 定義為：

- 可以選擇一些 element 將其刪除，使得剩下的 element 都是相同的值。

e.g.

1. $nums = [4, 6, 1, 2]$ ， $k = 2$

   - 可以選擇 `[4, 6, 2]` 各自經過操作後會變成 `[4, 4, 4]`，因此 `beauty subsequence` 的最大長度為 3。

2. $nums = [1, 1, 1, 1]$ ， $k = 10$

   - 可以選擇 `[1, 1, 1, 1]` 各自經過操作後會變成 `[1, 1, 1, 1]`，因此 `beauty subsequence` 的最大長度為 4。

## 解題思路

### 1. Sorting and Sliding Window

對於 `nums[i]` 來說，經過操作後 `nums[i]` 的範圍可以變成 `[nums[i] - k, nums[i] + k]`，在這個範圍內的 `nums[j]` 都能和 `nums[i]` 組合成 `beauty subsequence`，因此只要兩數之間的距離為 $abs(nums[i] - num[j]) \leq 2k$ ，則能保證兩數能組合成 `beauty subsequence`。

因此，我們可以先對 `nums` 做排序，接著使用 sliding window 來遍歷 `nums`，對於 `nums[i]` 而言，只要其後面的 `nums[j]` 和 `nums[i]` 的距離小於等於 $2k$ 就能組合成 `beauty subsequence`，把符合條件的 `nums[j]` 加入 sliding window 中，並且將 sliding window 的右邊界向右移動，直到 `nums[j]` 和 `nums[i]` 的距離大於 $2k$ 為止，此時 sliding window 的長度即為包含 `nums[i]` 的 `beauty subsequence` 的最大長度，也就是 $j - i + 1$ 。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    int maximumBeauty(std::vector<int> &nums, int k) {
        std::sort(nums.begin(), nums.end());

        // right 表示 sliding window 的右邊界
        int res = 0, right = 0, n = nums.size();
        for (int i = 0; i < n && right < n; ++i) {
            // 滑動 window 的右邊界，直到 nums[i] 和 nums[right] 距離超過 2k
            while (right < n && nums[i] + k * 2 >= nums[right]) {
                ++right;
            }
            // 更新 beauty subsequence 的最大長度
            res = std::max(res, right - i);
        }

        return res;
    }
};
```

[![](https://i.imgur.com/E2HA3i3.png)](https://i.imgur.com/E2HA3i3.png)

#### 複雜度分析

令 $n$ 為 `nums` 的長度。

- 時間複雜度： $O(n \log n)$

- 空間複雜度： $O(1)$

### 2. Difference Array（差分數組）

對 `nums[i]` 經過操作後 `nums[i]` 的範圍可以變成 `[nums[i] - k, nums[i] + k]`，可以理解成在這個範圍內的數字的出現次數都 + 1，因此可以用差分數組來紀錄發生變化的區間位置，`nums[i]` 出現次數增加的起始位置為 $nums[i] - k$ ，結束位置為 $nums[i] + k + 1$ ，只記錄起始位置和結束位置的變化，最後再計算 prefix sum 即可得到每個 element 的出現頻率，最大值即為答案。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    int maximumBeauty(std::vector<int> &nums, int k) {
        int max_num = *std::max_element(nums.begin(), nums.end());
        std::vector<int> cnt(max_num + 2); // cnt[max_num + 1] 用於處理邊界條件

        for (int num : nums) {
            // nums[i] 可變換的範圍為 [nums[i] - k, nums[i] + k]
            // 出現頻率增加的起始位置為 nums[i] - k，出現頻率下降的位置為 nums[i] + k + 1
            ++cnt[std::max(num - k, 0)];
            --cnt[std::min(num + k + 1, max_num + 1)];
        }

        // 計算 prefix sum 即可得到每個 element 的出現頻率，最大值為答案
        int res = 0, count = 0;
        for (int c : cnt) {
            count += c;
            res = std::max(res, count);
        }

        return res;
    }
};
```

[![](https://i.imgur.com/kPoDd4T.png)](https://i.imgur.com/kPoDd4T.png)

#### 複雜度分析

令 $m$ 為 `nums` 中最大的數字。

- 時間複雜度： $O(m)$

- 空間複雜度： $O(m)$
