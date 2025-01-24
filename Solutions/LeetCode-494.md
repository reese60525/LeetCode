# <center> [LeetCode - 494. Target Sum](https://leetcode.com/problems/target-sum/description/) </center>

## 題目敘述

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241210161121016.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241210161121016.png)

給定一個整數陣列 `nums` 和一個整數 `target`，對 `nums` 中每個 `nums[i]` 進行**加法**或是**減法**，找出將整個 `nums` 經過**加法**或**減法**後總為 `target` 的方法數。

e.g.

$nums = [1, 1, 1, 1, 1]$ ， $target = 3$ ，共有以下幾種方式可以使 `nums` 總和等於 `target`：

1. $+1 +1 +1 +1 -1 = 3$

2. $+1 +1 +1 -1 +1 = 3$

3. $+1 +1 -1 +1 +1 = 3$

4. $+1 -1 +1 +1 +1 = 3$

5. $-1 +1 +1 +1 +1 = 3$

答案為 5。

該題目的 `nums` 的 element 只能使用一次，因此這是一個 0-1 背包問題。

## 解題思路

### 1. Backtracking Algorithm

每個 `nums[i]` 有兩種選擇，分別為 `+` 和 `-`，因此可以將每個 `nums[i]` 當作一個節點，並且將每個節點的兩個子節點分別為 `+` 和 `-`，最後將所有可能的路徑加總起來，即可得到答案。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    int backtrack(std::vector<int> &nums, int target, int index) {
        // 當 index = nums 的長度時，表示已經遍歷完所有 element，
        // 此時檢查 target 是否為 0，若為 0 則表示找到一種方法，返回 1，否則返回 0
        if (index == nums.size()) {
            return target == 0;
        }

        // 對於當前的 nums[index] 有 + 和 - 兩種選擇
        return backtrack(nums, target - nums[index], index + 1) + backtrack(nums, target + nums[index], index + 1);
    }
    int findTargetSumWays(std::vector<int> &nums, int target) {
        return backtrack(nums, target, 0);
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241206180151624.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241206180151624.png)

#### 複雜度分析

令 $n$ 為 `nums` 的長度。

- 時間複雜度： $O(2^n)$

- 空間複雜度： $O(n)$

### 2. Dynamic Programming（DP）

假設 `sum` 為 **`nums` 中所有 element 的總和**，`positive` 是**用加法的所有 element 總和**，`negative` 是**用減法的所有 element 總和**，則有以下關係式:

1. $sum = positive + negative$

2. $target = positive - negative$

3. $positive \times 2 = target + sum$

4. $positive = \frac {target + sum}{2}$

觀察第四個關係式，可得兩點結論:

1. 由於 `positive` **必定大於等於 0**，因此當 $target + sum$ 為**負數**時，表示此題**無解**。

2. $target + sum$ **必須為偶數**，否則 `positive` 將會是**浮點數**，不符合題目要求。

經過以上的推導，該問題變成了**從 `nums` 中選擇一些 element，使得其總和為 $\frac {target + sum}{2}$**，這個問題可以轉換成 0-1 背包問題，並且使用動態規劃來解決。

令 `i` 為 `nums` 的 index， $j = \frac {target + sum}{2}$ 。`nums` 中的 element 都有**選**和**不選**兩種情況，如果選擇了 `nums[i]`，則 `j` 就會減少 `nums[i]`，否則 `j` 不變，由此可得遞迴公式如下：

$$
dfs[i][j] = dfs[i - 1][j] + dfs[i - 1][j - nums[i]]
$$

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    int dfs(std::vector<int> &nums, int index, int sum) {
        // 當 nums 中所有 element 都遍歷過後，確認 sum 是否為 0
        if (index < 0) {
            return sum == 0;
        }

        // 若 sum 小於 nums[index]，扣掉 nums[index] 後會變成負數，需要跳過
        if (sum < nums[index]) {
            return dfs(nums, index - 1, sum);
        }

        // 分別計算選擇 nums[index] 與不選擇 nums[index] 的結果，加總並回傳
        return dfs(nums, index - 1, sum) + dfs(nums, index - 1, sum - nums[index]);
    }

    int findTargetSumWays(std::vector<int> &nums, int target) {
        // 計算 nums 和 sum 的總和
        int sum = target;
        for (int n : nums) {
            sum += n;
        }

        // 若總和為負數或是奇數，表示此題無解
        if (sum < 0 || sum % 2 == 1) {
            return 0;
        }

        sum /= 2; // positive = sum / 2
        return dfs(nums, nums.size() - 1, sum);
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241206180028424.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241206180028424.png)

#### 複雜度分析

令 $n$ 為 `nums` 的長度。

- 時間複雜度： $O(2 ^ n)$

- 空間複雜度： $O(n)$

---

將以上程式碼由遞迴轉換成動態規劃（DP）

在遞迴寫法中的邊界條件為:

```cpp {.line-numbers}
if (index < 0) {
    return sum == 0;
}
```

這時的 $index = -1$ ，因此可以將 `dp` 的大小設為 $(nums.size() + 1)\times (sum + 1)$ ， $nums.size() + 1$ 多出來的 1 是為了處理邊界條件中 $index = -1$ 的情況，防止 index out of range，而 $sum + 1$ 是因為 `sum` 的範圍為 `[0, sum]` 共 $sum + 1$ 種情況。

根據遞迴中的邊界條件，可以將 `dp` 的初始值設為 $dp[0][0] = 1$ ，表示當 $index = -1$ 且 $sum = 0$ 時，有 1 種方法可以湊出總額。

將遞迴 code：

```cpp {.line-numbers}
if (sum < nums[index]) {
    return dfs(nums, index - 1, sum);
}

return dfs(nums, index - 1, sum) + dfs(nums, index - 1, sum - nums[index]);
```

轉換成 DP code：

```cpp {.line-numbers}
if (j < nums[i]) {
    dp[i + 1][j] = dp[i][j];
}
else {
    dp[i + 1][j] = dp[i][j] + dp[i][j - nums[i]];
}
```

由於為了處理 $index = -1$ 的情況，`dp[][]` 的 `row` 有多 +1，因此 `dp[][]` 中的 `row` 都需要額外 +1。

可以想像成原本dp長這樣:

$row = 3$ ， $col = 4$

| - | - | - | - |
|---|---|---|---|
| - | - | - | - |
| - | - | - | - |

為了處理 $index = -1$ 的情況，將 $row + 1$ ，因此變成:

| - | - | - | - |
|---|---|---|---|
| - | - | - | - |
| - | - | - | - |
| - | - | - | - |

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    int findTargetSumWays(std::vector<int> &nums, int target) {
        // 計算 nums 和 sum 的總和
        int sum = target;
        for (int n : nums) {
            sum += n;
        }

        // 若總和為負數或是奇數，表示此題無解
        if (sum < 0 || sum % 2 == 1) {
            return 0;
        }

        sum /= 2; // positive = sum / 2
        // 將 row 多 +1，避免 index = -1 的情況
        std::vector<std::vector<int>> dp(nums.size() + 1, std::vector<int>(sum + 1, 0));
        dp[0][0] = 1; // 初始狀態

        // 計算每個 dp[i][j] 的解
        for (int i = 0; i < nums.size(); ++i) {
            for (int j = 0; j < sum + 1; ++j) {
                if (j < nums[i]) {
                    dp[i + 1][j] = dp[i][j];
                }
                else {
                    dp[i + 1][j] = dp[i][j] + dp[i][j - nums[i]];
                }
            }
        }

        return dp[nums.size()][sum];
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241206183655096.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241206183655096.png)

#### 複雜度分析

令 $n$ 為 `nums` 的長度， $sum = \dfrac{sum(nums) + target}{2}$ 。

- 時間複雜度： $O(n \cdot sum)$

- 空間複雜度： $O(n \cdot sum)$

---

對於上面的 DP code 可以進一步將 `dp` 的空間優化。

觀察 DP 狀態轉移公式：

$$
dp[i][j] = dp[i - 1][j] + dp[i - 1][j - nums[i]]
$$

可以發現每次計算 `dp[i][j]` 時，只會用到 `dp[i - 1][j]` 和 `dp[i - 1][j - nums[i]]`，而 `dp[i-1]、dp[i-2] ... dp[0]` 都不會再被使用到。

舉例來說如下所示：

| dp[]  | dp[][0] | dp[][1] | dp[][2] | dp[][3] | dp[][4] | dp[][4] | dp[][5] |
|-------|---------|---------|---------|---------|---------|---------|---------|
| dp[0] | -       | -       | -       | -       | -       | -       | -       |
| dp[1] | -       | -       | -       | -       | -       | -       | -       |
| dp[2] | -       | -       | -       | -       | -       | -       | -       |
| dp[3] | -       | -       | -       | -       | -       | -       | -       |

- `dp[0]`： `dp[0][0]` 初始化為 1，其餘 `dp[0][j]` 不會進入 DP 狀態轉移公式中。

- `dp[1]`： 由 `dp[0]` 轉變而成，只有使用到 `dp[0]`。

- `dp[2]`： 由 `dp[1]` 轉變而成，只有使用到 `dp[1]`。

- `dp[3]`： 由 `dp[2]` 轉變而成，只有使用到 `dp[2]`。

觀察以上範例的規律，可以統整出兩個結論：

1. 計算完 `dp[i]` 後 `dp[i-1]` 不會再被用到，因此可以將 `dp[i+1]` 的計算結果存放到 `dp[i-1]` 中

2. 計算完 `dp[i+1]` 後 `dp[i]` 不會再被用到，因此可以將 `dp[i+2]` 的計算結果存放到 `dp[i]` 中。

最後會變成這樣的循環:

- 計算完 `dp[i+1]` 並放入 `dp[i-1]`，此時 `dp[i]` 不會再被用到

- 計算完 `dp[i+2]` 並放入 `dp[i]`，此時 `dp[i+1]` 不會再被用到

- 計算完 `dp[i+3]` 並放入 `dp[i+1]` 也就是 `dp[i-1]` 的位置，此時 `dp[i+2]` 不會再被用到

- 計算完 `dp[i+4]` 並放入 `dp[i+2]` 也就是 `dp[i]` 的位置，此時 `dp[i+3]` 不會再被用到

- ...... 以此類推

由以上循環可得知總共只需要 `dp[0][]` 和 `dp[1][]` 兩個 `row` 來計算 `dp[i][j]`。

其中 `dp[i]` 的循環可以用 `& 1` 運算（也就是 mod 2） 來達成交替覆蓋資料的效果。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    int findTargetSumWays(std::vector<int> &nums, int target) {
        // 計算 nums 和 sum 的總和
        int sum = target;
        for (int n : nums) {
            sum += n;
        }

        // 若總和為負數或是奇數，表示此題無解
        if (sum < 0 || sum & 1) {
            return 0;
        }

        sum /= 2; // positive = sum / 2
        // 將 row 數量改為 2
        std::vector<std::vector<int>> dp(2, std::vector<int>(sum + 1, 0));
        dp[0][0] = 1; // 初始狀態

        // 計算每個 dp[i][j] 的解
        for (int i = 0; i < nums.size(); ++i) {
            for (int j = 0; j < sum + 1; ++j) {
                // 將 dp 的 row 都 & 1，達到交替覆蓋資料的效果
                if (j < nums[i]) {
                    dp[(i + 1) & 1][j] = dp[i & 1][j];
                }
                else {
                    dp[(i + 1) & 1][j] = dp[i & 1][j] + dp[i & 1][j - nums[i]];
                }
            }
        }

        // row 需要 & 1 才能取得正確的結果
        return dp[nums.size() & 1][sum];
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241206190443154.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241206190443154.png)

#### 複雜度分析

令 $n$ 為 `nums` 的長度， $sum = \dfrac{sum(nums) + target}{2}$ 。

- 時間複雜度： $O(n \times sum)$

- 空間複雜度： $O(sum)$

---

那麼能不能更進一步優化掉 `dp` 中的 `row` 呢？答案是可以的。

根據 $dp[i][j] = dp[i - 1][j] + dp[i - 1][j - nums[i]]$ 來模擬 DP 狀態轉移過程。

假設現在的 `dp` 只有一維，`dp[i]` 和 `dp[i+1]` **都使用同個陣列**，當 $nums[i] = 2$ 時，有以下 dp 狀態:

| dp[]    | dp[][0] | dp[][1] | dp[][2] | dp[][3] | dp[][4] | dp[][4] | dp[][5] |
|---------|:-------:|:-------:|:-------:|:-------:|:-------:|:-------:|:-------:|
| dp[i]   |    1    |    2    |    3    |    4    |    5    |    6    |    7    |
| dp[i+1] |    -    |    -    |    -    |    -    |    -    |    -    |    -    |

因為 $j < nums[i]$ ，所以 `dp[i+1][0]` 和 `dp[i+1][1]` 的狀態不改變。

| dp[]    | dp[][0] | dp[][1] | dp[][2] | dp[][3] | dp[][4] | dp[][4] | dp[][5] |
|---------|:-------:|:-------:|:-------:|:-------:|:-------:|:-------:|:-------:|
| dp[i]   |    1    |    2    |    3    |    4    |    5    |    6    |    7    |
| dp[i+1] |    1    |    2    |    -    |    -    |    -    |    -    |    -    |

$dp[i+1][2] = dp[i][2] + dp[i][0] = 3 + 1 = 4$ 。

| dp[]    | dp[][0] | dp[][1] | dp[][2] | dp[][3] | dp[][4] | dp[][4] | dp[][5] |
|---------|:-------:|:-------:|:-------:|:-------:|:-------:|:-------:|:-------:|
| dp[i]   |    1    |    2    |    3    |    4    |    5    |    6    |    7    |
| dp[i+1] |    1    |    2    |    4    |    -    |    -    |    -    |    -    |

$dp[i+1][3] = dp[i][3] + dp[i][1] = 4 + 2 = 6$ 。

| dp[]    | dp[][0] | dp[][1] | dp[][2] | dp[][3] | dp[][4] | dp[][4] | dp[][5] |
|---------|:-------:|:-------:|:-------:|:-------:|:-------:|:-------:|:-------:|
| dp[i]   |    1    |    2    |    3    |    4    |    5    |    6    |    7    |
| dp[i+1] |    1    |    2    |    4    |    6    |    -    |    -    |    -    |

**接下來是重點**

$dp[i+1][4] = dp[i][4] + dp[i][2] = 5 + 4 = 9$ ，但是 `dp[i][2]` 的值已經被 `dp[i+1][2]` 覆蓋，從原本的 $3$ 變成 $4$，所以此時 $dp[i+1][4] = 9$ 是**錯誤的**，正確的值應該是 8。

| dp[]    | dp[][0] | dp[][1] | dp[][2] | dp[][3] |   dp[][4]   | dp[][4] | dp[][5] |
|---------|:-------:|:-------:|:-------:|:-------:|:-----------:|:-------:|:-------:|
| dp[i]   |    1    |    2    |    3    |    4    |      5      |    6    |    7    |
| dp[i+1] |    1    |    2    |    4    |    6    | **9(錯誤)** |    -    |    -    |

那麼該怎麼做才能得到正確的值呢？很簡單，只要將 `dp[i][]` 的計算方式從原本的 `dp[i][0]` 開始算，改成從 `dp[i][j]` 開始算，也就是從最後一個往第一個算就可以得到正確的值。

至於為什麼這樣做可以得到正確的值，是因為 `dp[i][j]` 的狀態轉移計算需要使用到**其左邊轉換前的值**，因此如果從右邊開始算，就可以確保其用到的**左邊的值都是尚未被覆蓋的正確值**。

最後，DP 狀態轉移方程式由：

$$
dp[i][j] = dp[i - 1][j] + dp[i - 1][j - nums[i]]
$$

被簡化成：

$$
dp[j] = dp[j] + dp[j - nums[i]]
$$

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    int findTargetSumWays(std::vector<int> &nums, int target) {
        // 計算 nums 和 sum 的總和
        int sum = target;
        for (int n : nums) {
            sum += n;
        }

        // 若總和為負數或是奇數，表示此題無解
        if (sum < 0 || sum % 2 == 1) {
            return 0;
        }

        sum /= 2; // positive = sum / 2
        // 改成一維陣列
        std::vector<int> dp(sum + 1, 0);
        dp[0] = 1; // 初始狀態

        // 計算每個 dp[i][j] 的解
        for (int i = 0; i < nums.size(); ++i) {
            // 從後面開始計算，j < nums[i] 的值不會被改變因此不用計算
            for (int j = sum; j >= nums[i]; --j) {
                dp[j] = dp[j] + dp[j - nums[i]];
            }
        }

        return dp[sum];
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241206194532028.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241206194532028.png)

#### 複雜度分析

令 $n$ 為 `nums` 的長度， $sum = \dfrac{sum(nums) + target}{2}$ 。

- 時間複雜度： $O(n \cdot sum)$

- 空間複雜度： $O(sum)$

[參考資料](https://www.bilibili.com/video/BV16Y411v7Y6/?vd_source=2cf43c238d6ab7b940d94a7bbf36cc0c)
