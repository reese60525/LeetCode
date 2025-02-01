# <center> [LeetCode - 1760. Minimum Limit of Balls in a Bag](https://leetcode.com/problems/minimum-limit-of-balls-in-a-bag/description/) </center>

## 題目敘述

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241210161159467.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241210161159467.png)

給一個整數陣列 `nums` 和一個整數 `maxOperations`，每次操作可以將 `nums` 中的任意一個 element `nums[i]` 分成兩個不為 0 的整數，`maxOperations` 是最多可以進行操作的次數，求對 `nums` 進行操作後，`nums` 中的最大值最小可以是多少。

e.g.

1. $nums = [9]$ ， $maxOperations = 2$ 。

    能操作 2 次，因此能分成 3 部分， $nums = [3, 3, 3]$ ，因此答案為 3。

1. $nums = [10]$ ， $maxOperations = 2$ 。

    能操作 2 次，因此能分成 3 部分， $nums = [3, 3, 4]$ ，因此答案為 4。

1. $nums = [9]$ ， $maxOperations = 3$ 。

    能操作 3 次，因此能分成 4 部分， $nums = [2, 2, 2, 3]$ ，因此答案為 3。

1. $nums = [10]$ ， $maxOperations = 3$ 。

    能操作 3 次，因此能分成 4 部分， $nums = [2, 2, 3, 3]$ ，因此答案為 3。

1. $nums = [2, 4, 8, 2]$ ， $maxOperations = 4$ 。

    能操作 4 次，因此能分成 5 部分， $nums = [2, 2, 2, 2, 2, 2, 2, 2]$ ，因此答案為 2。

## 解題思路

### 1. Brute Force

首先要找出這個問題的 `lower bound`，`lower bound` 代表該問題的答案最小是多少，`sum` 為 `nums` 的總和，`k` 是指最多能將 `nums` 分成 `k` 份， $k = numsSize + maxOperations$ ，而 $lower bound = \frac{sum}{k}$ 。

遍歷 `nums`，如果 $nums[i] > lower bound$ ，則要 `nums[i]` 分成 `n` 份使這 `n` 份新的 `num` 都小於等於 `lower bound`，而將一個數分成 `n` 份需要 `x`次操作，將這些 `x` 累加，結束遍歷後如果 $x > maxOperations$ ，表示 `lower bound` 太小，需要將 $lower bound + 1$ 並重新遍歷一次，反之則表示找到答案為 `lower bound`。

`n` 和 `x` 的計算方式，由以下例子可以得知：

令 $nums[i] = 10$ ， $lower bound = 3$

要將 `nums[i]` 分成全部都小於等於 `lower bound` 的數，可以用 $n = \frac{nums[i]}{lower bound}$ 得知能分成 $n = 3.3333...$ 份，由於不能分成小數份，因此要將 `n` 向上取整數變成 4 份，公式為: $n = (\frac{nums[i]}{lower bound}) + (nums[i] \mod lower bound \neq 0)$ 。

將一個數分成 `n` 份則需要 $n - 1$ 次操作，例如將 6 分成 3 份，第一次將 6 分成 2 和 4，第二次將 4 分成 2 和 2，共 2 次操作，公式為： $x = n - 1$ 。

那能不能將 `n` 的計算再簡化呢？答案是可以的。觀察以下例子：

**這些例子的除法都是整數除法，也就是無條件捨去小數部分**。

1. $nums[i] = 9$ ， $lower bound = 3$

    $n = \frac{9}{3} + ((9 \mod 3) \neq 0) = 3 \text{，} x = 3 - 1 = 2$

2. $nums[i] = 10$ ， $lower bound = 3$

    $n = \frac{10}{3} + ((10 \mod 3) \neq 0) = 4 \text{，} x = 4 - 1 = 3$

3. $nums[i] = 11$ ， $lower bound = 3$

    $n = \frac{11}{3} + ((11 \mod 3) \neq 0) = 4 \text{，} x = 4 - 1 = 3$

4. $nums[i] = 12$ ， $lower bound = 3$

    $n = \frac{12}{3} + ((12 \mod 3) \neq 0) = 4 \text{，} x = 4 - 1 = 3$

5. $nums[i] = 13$ ， $lower bound = 3$

    $n = \frac{13}{3} + ((13 \mod 3) \neq 0) = 5 \text{，} x = 5 - 1 = 4$

從以上可以發現規律，使得`x`的公式能簡化為 $x = \frac{nums[i] - 1}{lower bound}$ 。

#### 程式碼

```c++
class Solution {
  public:
    int minimumSize(std::vector<int> &nums, int maxOperations) {
        // 計算 lower bound
        int lower_bound = 0;
        for (int n : nums) {
            // 避免整數 overflow
            lower_bound = (lower_bound + n) % n;
        }
        lower_bound /= (nums.size() + maxOperations);
        lower_bound = lower_bound == 0 ? 1 : lower_bound; // 至少要 1

        std::sort(nums.begin(), nums.end());
        while (true) {
            int op_count = 0; // 計算操作次數
            for (int i = nums.size() - 1; i >= 0; --i) {
                // 操作次數超過上限就可以跳出迴圈了
                if (op_count > maxOperations) {
                    break;
                }
                // 大於 lower_bound 的數需要被分成 x 堆
                if (nums[i] > lower_bound) {
                    op_count += (nums[i] - 1) / lower_bound;
                }
            }
            if (op_count > maxOperations) {
                lower_bound++;
            }
            else {
                return lower_bound;
            }
        }

        // 保證有解，不會到這裡
        return -1;
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241207121820774.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241207121820774.png)

#### 複雜度分析

令 `n` 為 `nums` 的長度， $\max(nums)$ 為 `nums` 中最大的數。

- 時間複雜度： $O(\max(nums) \cdot n)$

    考慮到最差情況，`nums` 有 $10^4$ 個 $10^9$ ， $maxOperations = 1$ ，則 $lower bound = 10^5$ ，只有當 $lower bound = 10^9$ 時才找到答案，外部迴圈共要執行 $10^9 - 10^5 \approx 10^9$ 次，內部迴圈每次要執行 $10^4$ 次。

- 空間複雜度： $O(1)$

### 2. Binary Search

原本暴力解的概念是找出一個可能的答案的最小值 `lower bound`，然後慢慢累加並再驗證這個答案是否可行。

可以換個方式，將答案的範圍定為 `[1, max(nums)]` 對這個範圍進行 binary search，令 $l = 1$ 、 $r = \max(nums)$ 、 $mid = (l + r) / 2$ ，每次都檢查 `mid` 是不是可行的答案，如果可行表示 `[mid, r]` 這個範圍都是可行的，將答案範圍縮小到左半邊 `[l,mid]`，反之若不可行則縮小到右半邊 `[mid + 1, r]`，當 binary search 結束後，`r` 就是答案。

需要注意的是在更新範圍時，如果要將範圍縮小至左半邊，則 $r = mid$ 而不是 $r = mid - 1$ ，因為 `mid` 有可能就是答案所以不能排除 `mid`。

舉例來說：

$nums = [n1,  n2, n3, n4, n5, n6]$ ，如果當前 `mid` 是答案且 $mid = n3$ ，若是 $r = mid - 1$ ，則下次搜索範圍會變成 `[l, n2]`，這範圍內沒有真正的答案，導致錯過答案。

#### 程式碼

```c++
class Solution {
  public:
    int minimumSize(std::vector<int> &nums, int maxOperations) {
        int max_num = 0; // 計算 upper bound
        for (int n : nums) {
            max_num = std::max(max_num, n);
        }

        int l = 1, r = max_num;
        while (l < r) {
            int mid = (l + r) / 2;
            int op_count = 0; // 計算當前操作次數

            for (int n : nums) {
                // 跳過不用操作的數，避免無所謂的除法運算
                if (n > mid) {
                    op_count += (n - 1) / mid;
                }
            }

            if (op_count > maxOperations) {
                l = mid + 1;
            }
            else {
                r = mid;
            }
        }

        return r;
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241207110037985.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241207110037985.png)

#### 複雜度分析

令 `n` 為 `nums` 的長度， $\max(nums)$ 為 `nums` 中最大的數。

- 時間複雜度: $O(n \cdot log(\max(nums)))$

- 空間複雜度: $O(1)$
