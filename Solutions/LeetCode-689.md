# <cneter> [689. Maximum Sum of 3 Non-Overlapping Subarrays](https://leetcode.com/problems/maximum-sum-of-3-non-overlapping-subarrays/description/) </center>

## 題目敘述

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures202412290245584.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures202412290245584.png)

給一個整數 `k` 和整數陣列 `nums`，找出三個長度為 `k` 且不重疊的 subarray，使其相加的總和最大，回傳每個 subarray 的起始 index，若有多組解則回傳 index 字典序最小的一組。

## 解題思路

### 1. Dynamic Programming（DP）

每個 subarray 都不能重疊，只能選三個，這就是一種 0-1 背包問題，對於每個以 $index = i$ 當作**結束**位置的 subarray，都有選或是不選兩種選擇，因此能得到以下遞迴 code：

```cpp {.line-numbers}  
int dfs(int i, int j, const std::vector<int> &sum, const int &k) {
    // 當 j = 0 時表示 subarray 都選完了
    if (j == 0) {
        return 0;
    }
    // 剩下 i + 1 個數字不足以湊出 `j` 個長度為 k 的 subarray，因此無效
    if (i + 1 < j * k) {
        return INT_MIN;
    }

    // 選和不選兩者之間取較大值
    return std::max(dfs(i - 1, j, sum, k), dfs(i - k, j - 1, sum, k) + sum[i]);
}
```

`sum` 表示以 `i` 為終點的 subarray 總和，`dfs[i][j]` 表示在 $index =  i$ 時還剩下 `j` 個 subarray 要選擇，當 $j = 0$ 表示都選完了不用再找，若 $i + 1 < j \cdot k$ 表示剩下的數字數量不足以湊出 `j` 個長度為 `k` 的 subarray，因此回傳 `INT_MIN` 表示無效。當選擇了以 `i` 當作起始位置的 subarray 時，該 subarray 的範圍是 `[i - k + 1, i]`,因此 `i` 下個位置為 $i - k$ 才不會重疊。

根據 `dfs` 可得遞迴式：

$$
dfs(i, j) =
\begin{cases}
0 & j = 0 \\
INT\_MIN & i + 1 < j \cdot k \\
\max(dfs(i - 1, j), dfs(i - k, j - 1) + sum[i]) & \text{otherwise}
\end{cases}
$$

轉為 DP 狀態轉移方程式：

$$
dp[i][j] =
\begin{cases}
0 & j = 0 \\
INT\_MIN & i + 1 < j \cdot k \\
\max(dp[i - 1][j], dp[i - k][j - 1] + sum[i]) & \text{otherwise}
\end{cases}
$$

令 `n` 為 `nums` 長度，`dp[i][j]` 表示在 `[0, i-1]` 的 `nums` 範圍中，也就是前 `i` 個數字中選 `j` 個 subarray 的最大值，如果選了第 `i` 個數字，那麼該 subarray 的範圍為第 $i-k+1$ 到第 $i$ 個數字，在 `nums` 中的 index 為 `[i - k, i - 1]` 之間，此時將前 $i-k$ 個數字選 $j - 1$ 個 subarray 的最大值 `dp[i-k][j-1]` 加上當前選擇的 subarray 的總和，拿去和**不選擇**當前 subarray 的總和比較取較大值。遍歷完畢後 `dp[n][3]` 就是整個 `nums` 範圍中選擇 3 個 subarray 的最大值。

接著再從 `dp[n][3]` 遍歷 `dp` 來回溯找出每個 subarray 的起始位置，如果 $dp[i][j] = dp[i-1][j]$ ，表示以第 `i` 個數字為終點的 subarray 沒有被選擇，跳過繼續找，若 $dp[i][j] \neq dp[i-1][j]$ ，表示以第 `i` 個數字為終點的 subarray 有被選擇，該 subarray 的起始位置為第 $i - k + 1$ 個數字，對應到 `nums` 中的 index 為 $i - k$ ，將該 index 加入 `res` 中，並將 $j - 1$ 表示還剩下 $j - 1$ 個 subarray 要找。

e.g.

- $nums = [2, 3, 3, 2, 2, 3, 3, 2, 3, 3, 2, 3, 2, 3, 3]$ ， $k = 2$ 。

- $i = n = 14$ ， $j = 3$ ， $dp[][3] = [0, 0, 0, 0, 0, 0, 15, 16, 16, 17, 18, 18, 18, 18, 18, 18]$

  計算後的 `dp[][3]`如上，表示前 `i` 個數字中選擇 3 個 subarray 的最大值，`dp[10][3]` 和 `dp[9][3]` 的值不同，代表選擇了以第 10 個數字為終點的 subarray，該 subarray 的起始位置為第 $i - k + 1 = 10 - 2 + 1 = 9$ 個數字，對應到`nums` 中的 index 為 8，將 8 放入 `res[2]` 中， $i = i - k = 10 - 2 = 8$ ， $j = 3 - 1 = 2$ 。

- $i = 8$ ， $j = 2$ ， $dp[][2] = [0, 0, 0, 0, 10, 10, 11, 12, 12]$ 。

  計算後的前 8 個數字的 `dp[][2]`如上，表示前 `i` 個數字中選擇 2 個 subarray 的最大值，`dp[7][2]` 和 `dp[6][2]` 的值不同，代表選擇了以第 7 個數字為終點的 subarray，該 subarray 的起始位置為第 $i - k + 1 = 7 - 2 + 1 = 6$ 個數字，對應到`nums` 中的 index 為 5，將 5 放入 `res[1]` 中， $i = i - k = 7 - 2 = 5$ ， $j = 2 - 1 = 1$ 。

- $i = 5$ ， $j = 1$ ， $dp[][1] = [0, 0, 5, 6, 6, 6]$ 。
  計算後的前 5 個數字的 `dp[][1]`如上，表示前 `i` 個數字中選擇 1 個 subarray 的最大值，`dp[3][1]` 和 `dp[2][1]` 的值不同，代表選擇了以第 3 個數字為終點的 subarray，該 subarray 的起始位置為第 $i - k + 1 = 3 - 2 + 1 = 2$ 個數字，對應到`nums` 中的 index 為 1，將 1 放入 `res[0]` 中， $i = i - k = 3 - 2 = 1$ ， $j = 1 - 1 = 0$ 。

- 全部的 subarray 都找完了， $res = [1, 5, 8]$ 。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    std::vector<int> maxSumOfThreeSubarrays(std::vector<int> &nums, int k) {
        int n = nums.size();

        // 計算 preffix sum，sum[i] 表示前 `i` 個 `nums` 的總和
        std::vector<int> sum(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            sum[i] = sum[i - 1] + nums[i - 1];
        }

        // dp[i][j] 表示前 `i` 個數字中，選擇 `j` 個長度為 `k` 的子數組的最大總和
        int dp[n + 1][4];
        std::memset(dp, 0, sizeof(dp));
        for (int i = k; i <= n; ++i) {
            for (int j = 1; j <= 3; ++j) {
                // 目前能選的數字數量至少要為 `j` 個長度 `k` 的子數組總長度才是有意義的
                if (i < j * k) {
                    dp[i][j] = INT_MIN;
                    continue;
                }
                dp[i][j] = std::max(dp[i - 1][j], dp[i - k][j - 1] + sum[i] - sum[i - k]);
            }
        }

        // 回朔找出選擇的 subarray 的最小字典序的起始 index
        // 若 dp[i][cnt] 不等於 dp[i - 1][cnt]，表示以第 `i` 個數字為結尾的 subarray 被選擇了
        // subarray 的起始位置是第 `i - k + 1` 個數字，在 `nums` 中的 index 是 `i - k`
        int i = n, j = 3;
        std::vector<int> res(3);
        while (j > 0) {
            if (dp[i][j] == dp[i - 1][j]) {
                --i;
                continue;
            }
            res[--j] = i - k;
            i -= k;
        }

        return res;
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures202412291417149.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures202412291417149.png)

#### 複雜度分析

令 $n$ 為 `nums` 的長度， $m$ 為要找的 subarray 的數量。

- 時間複雜度： $O(n)$

    由於這題 subarray 的數量固定為 3，因此 $O(n \cdot m) = O(3n) \approx O(n)$ 。

- 空間複雜度： $O(n)$

### 2. Prefix Max and Suffix Max

有 3 個 subarray 要找，可以先固定中間的 subarray，然後找左邊和右邊的最大 subarray。

首先為了快速計算出每個 subarray 的總和，先計算出 `nums` 的 prefix sum `sum`，接著創建兩個整數陣列 `left_max` 和 `right_max`，`left_max[i]` 表示在 `i` 左邊的最大 subarray 總和的起始 index，`right_max[i]` 表示在 `i` 右邊的最大 subarray 總和的起始 index，若是有總和相同的則選擇起始 index 較小的。

然後令 `max_val` 表示當前遇到的 3 個 subarray 最大總和，遍歷 `nums`，透過 `sum` 計算出 `i` 為起點的 subarray 和 `i` 左右兩邊的最大 subarray 的總和，和 `max_val` 比較，如果比 `max_val` 大，則更新 `max_val` 和 `res`。

***該方法只適於於 subarray 數量為 3 的情況***

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    std::vector<int> maxSumOfThreeSubarrays(std::vector<int> &nums, int k) {
        int n = nums.size();

        // sum[i]表示在 nums 範圍是 [0, i] 中的總合
        std::vector<int> sum(n, 0);
        sum[0] = nums[0];
        for (int i = 1; i < n; ++i) {
            sum[i] = sum[i - 1] + nums[i];
        }

        // left_max[i] 表示在 nums 範圍是 [0, i] 中總和最大的 subarray 的起始 index
        int max_val = sum[k - 1];
        std::vector<int> left_max(n, 0);
        for (int i = k; i < n; ++i) {
            int cur_val = sum[i] - sum[i - k];
            if (cur_val > max_val) {
                max_val = cur_val;
                left_max[i] = i - k + 1;
            }
            else {
                left_max[i] = left_max[i - 1];
            }
        }
        // right_max[i] 表示在 nums 範圍是 [i, n - 1] 中總和最大的 subarray 的起始 index
        max_val = sum[n - 1] - sum[n - k - 1];
        std::vector<int> right_max(n, n - k);
        for (int i = n - k - 1; i > 0; --i) {
            int cur_val = sum[i + k - 1] - sum[i - 1];
            // 當 max_val = cur_val，要選擇起始 index 較小的，所以是 >= 而不是 >
            if (cur_val >= max_val) {
                max_val = cur_val;
                right_max[i] = i;
            }
            else {
                right_max[i] = right_max[i + 1];
            }
        }

        int max_sum = 0;
        std::vector<int> res(3);
        // 遍歷中間的 subarray，找出最大的總和和各自的起始 index
        for (int i = k; i <= (n - 1) - (2 * k - 1); ++i) {
            int left_idx = left_max[i - 1];
            int left_val = left_idx == 0 ? sum[left_idx + k - 1] : sum[left_idx + k - 1] - sum[left_idx - 1];
            int right_idx = right_max[i + k];
            int right_val = sum[right_idx + k - 1] - sum[right_idx - 1];
            int cur_val = sum[i + k - 1] - sum[i - 1];

            if (left_val + cur_val + right_val > max_sum) {
                max_sum = left_val + cur_val + right_val;
                res[0] = left_idx;
                res[1] = i;
                res[2] = right_idx;
            }
        }

        return res;
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures202412291609594.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures202412291609594.png)

#### 複雜度分析

令 $n$ 為 `nums` 的長度。

- 時間複雜度： $O(n)$

- 空間複雜度： $O(n)$

### 3. Sliding Window

假設要找的 subarray 數量為 2，讓第一個 subarray 的 window 起始 index 為 `i`，第二個 subarray 的 window 起始 index 為 $i + k$ ，同時滑動兩個 window，並記錄 window1 的最大值 `w1_max` 和起始 index `w1_max_idx`，令當前遇到的 window1 和 window2 的最大和為 `w12_max`，將 `w1_max` 和 window2 當前總和 `w2_sum` 相加，如果大於 `w12_max` 則更新  `w12_max` 和 `res`，最後回傳 `res`。

為何這方法能成功？因為對於當前的 window2 而言，`w1_max` 永遠是 window2 的最優選，由於是同時滑動兩個 window，所以 `w1_max` 永遠都會在 window2 左邊，不會有重疊的問題，假設在 `i` 時 `w1_max` 更新了，但更新後的 `w1_max` 是當前 window2 的最優選並且也在 window2 左邊。

```cpp {.line-numbers}
class Solution {
  public:
    std::vector<int> maxSumOfThreeSubarrays(std::vector<int> &nums, int k) {
        int n = nums.size();

        std::vector<int> res(2);
        int w1_sum = 0, w1_max = 0, w1_max_idx = 0;
        int w2_sum = 0, w12_max = 0;
        for (int i = 0; i < n - k; ++i) {
            w1_sum += nums[i];
            w2_sum += nums[i + k];

            // 所有 window 的長度都是 `k` 後才開始計算
            if (i >= k - 1) {
                if (w1_sum > w1_max) {
                    w1_max = w1_sum;
                    w1_max_idx = i - (k - 1);
                }
                if (w1_max + w2_sum > w12_max) {
                    w12_max = w1_max + w2_sum;
                    res = {w1_max_idx, i + 1};
                }

                w1_sum -= nums[i - (k - 1)];
                w2_sum -= nums[i + 1];
            }
        }

        return res;
    }
};
```

而 subarray 數量為 3 時，做法就和 2 個 subarray 時一樣，只是多了一個 `w12_max` 要維護，`w12_max` 表示當前遇到的 window1 和 window2 的最大和，`w12_max_idx1` 和 `w12_max_idx2` 分別表示 `w12_max` 的 window1 和 window2 的起始 index。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    std::vector<int> maxSumOfThreeSubarrays(std::vector<int> &nums, int k) {
        int n = nums.size();

        std::vector<int> res(3);
        int w1_sum = 0, w1_max = 0, w1_max_idx = 0;
        int w2_sum = 0, w12_max = 0, w12_max_idx1 = 0, w12_max_idx2 = 0;
        int w3_sum = 0, w123_max = 0;
        for (int i = 0; i < n - 2 * k; ++i) {
            w1_sum += nums[i];
            w2_sum += nums[i + k];
            w3_sum += nums[i + 2 * k];

            // 所有 window 的長度都是 `k` 後才開始計算
            if (i >= k - 1) {
                if (w1_sum > w1_max) {
                    w1_max = w1_sum;
                    w1_max_idx = i - (k - 1);
                }
                if (w1_max + w2_sum > w12_max) {
                    w12_max = w1_max + w2_sum;
                    w12_max_idx1 = w1_max_idx;
                    w12_max_idx2 = i + 1;
                }
                if (w12_max + w3_sum > w123_max) {
                    w123_max = w12_max + w3_sum;
                    res = {w12_max_idx1, w12_max_idx2, i + k + 1};
                }

                w1_sum -= nums[i - (k - 1)];
                w2_sum -= nums[i + 1];
                w3_sum -= nums[i + k + 1];
            }
        }

        return res;
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures202412291952158.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures202412291952158.png)

#### 複雜度分析

令 $n$ 為 `nums` 的長度。

- 時間複雜度： $O(n)$

- 空間複雜度： $O(1)$
