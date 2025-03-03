# <center> [1509. Minimum Difference Between Largest and Smallest Value in Three Moves](https://leetcode.com/problems/minimum-difference-between-largest-and-smallest-value-in-three-moves/description/) </center>

## 題目敘述

[![](https://i.imgur.com/7dTPDdS.png)](https://i.imgur.com/7dTPDdS.png)

給一個整數陣列`nums`，最多可以選擇三個 element 將其值改為任意值，求操作後 `nums` 中最大值與最小值的差值最小是多少。

## 解題思路

### 1. Greedy and Sorting

要求的是最大值與最小值的差值，所以我們只在乎 `nums` 的極值，將 `nums` 升序排序後，共有以下四種移除方式：

1. 移除最小的三個值，此時最大和最小值的差值為 $diff = nums[n-1] - nums[3]$

2. 移除最小的兩個值與最大的值，此時最大和最小值的差值為 $diff = nums[n-2] - nums[2]$

3. 移除最小的值與最大的兩個值，此時最大和最小值的差值為 $diff = nums[n-3] - nums[1]$

4. 移除最大的三個值，此時最大和最小值的差值為 $diff = nums[n-4] - nums[0]$

找出這四種情況的最小值就是答案。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    int minDifference(std::vector<int> &nums) {
        // size 小於 5 的 必定為 0
        if (nums.size() < 5) {
            return 0;
        }

        int n = nums.size();
        std::sort(nums.begin(), nums.end());

        return std::min({
            nums[n - 4] - nums[0], // 移除最大的三個值
            nums[n - 3] - nums[1], // 移除最大的兩個值和最小的一個值
            nums[n - 2] - nums[2], // 移除最大的一個值和最小的兩個值
            nums[n - 1] - nums[3]  // 移除最小的三個值
        });
    }
};
```

[![](https://i.imgur.com/80TCDcK.png)](https://i.imgur.com/80TCDcK.png)

#### 複雜度分析

令 $n$ 為 `nums` 的長度。

- 時間複雜度： $O(n \log n)$

- 空間複雜度： $O(\log n)$

    `std::sort` 平均空間複雜度為 $O(\log n)$ 。

### 2. Greedy（Optimized）

優化方法一，由於我們只需要知道最大和最小的四個數，因此可以創建兩個 array 分別儲存最大和最小的四個數，遍歷 `nums` 時更新這兩個 array 即可，不需要排序整個 `nums`。

在底下的程式碼中，`func` 用於更新 `min_arr` 和 `max_arr`，`flag` 用於判斷現在的 array 是 `min_arr` 還是 `max_arr`，如果是 `max_arr` 則 $flag = -1$ ，反之 $flag = 1$ ，當更新 `max_arr` 時，在比較 `num` 和 `arr[idx]` 時各乘以 -1 來讓其比較的判斷邏輯和 `min_arr` 相同。

例如：

- 更新 `min_arr`：令 $min\_arr = [1, 2, 3, 5]$ ， $num = 1$

  遍歷 `min_arr` 直到有個 element > `num`，則該 element 可以被 `num` 取代，並且要從該 element 向後更新 `min_arr` 的值，更新後 $min\_arr = [1, 1, 2, 3]$ 。

- 更新 `max_arr`：令 $max\_arr = [8, 6, 5, 2]$ ， $num = 7$

  將 `num` 和 `max_arr` 都乘以 -1， $max\_arr = [-8, -6, -5, -2]$ ， $num = -7$ ，這樣就可以和 `min_arr` 使用相同的比較判斷邏輯。一樣先找到比 `num` 大的 element，然後從該 element 向後更新 `max_arr` 的值，更新後 $max\_arr = [-8, -7, -6, -5]$ ，再將 `max_arr` 乘以 -1 即可得到 `[8, 7, 6, 5]`，即為更新後的 `max_arr`。實際上只需要在比較時乘以 -1 即可，不需要真的將整個 `max_arr` 乘以 -1。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    int minDifference(std::vector<int> &nums) {
        // size 小於 5 的 必定為 0
        if (nums.size() < 5) {
            return 0;
        }

        // 維護前四大和前四小的 array
        auto func = [&](std::vector<int> &arr, int &num, int flag) -> void {
            int idx = 0, n = arr.size();
            // 找可以被 num 取代的 element
            while (idx < n && num * flag >= arr[idx] * flag) {
                ++idx;
            }
            // 從被取代的 element 向後更新
            if (idx < n) {
                for (size_t i = n - 1; i > idx; --i) {
                    arr[i] = arr[i - 1];
                }
                arr[idx] = num;
            }
        };

        // 找前四大和前四小的數
        std::vector<int> min_arr(4, INT_MAX), max_arr(4, INT_MIN + 1);
        for (int &num : nums) {
            func(min_arr, num, 1);
            func(max_arr, num, -1);
        }

        // i 表示最小的數有幾個被移除，則最大的數會有 3 - i 個被移除
        int res = INT_MAX;
        for (size_t i = 0; i < 4; ++i) {
            res = std::min(res, std::abs(min_arr[i] - max_arr[3 - i]));
        }

        return res;
    }
};
```

[![](https://i.imgur.com/XecPj8r.png)](https://i.imgur.com/XecPj8r.png)

#### 複雜度分析

令 $n$ 為 `nums` 的長度。

- 時間複雜度： $O(n)$

- 空間複雜度： $O(1)$
