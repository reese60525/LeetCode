# <center> [55. Jump Game](https://leetcode.com/problems/jump-game/description/) </center>

## 題目敘述

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501142018987.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501142018987.png)

給一個長度為 `n` 的整數陣列 `nums` 代表該位置最多可以往後跳躍的距離，請問能否從 `nums[0]` 跳到 `nums[n-1]`？

## 解題思路

### 1. Dynamic Programming（DP）

令 `dp[i]` 代表能否從 `nums[0]` 跳到 `nums[i]`，如果某個點 `dp[i]` 能夠跳到終點，且 `dp[j]` 能夠跳到 `dp[i]`，則 `dp[j]` 也能到達終點，可寫出以下 DP code：

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    bool canJump(std::vector<int> &nums) {
        int n = nums.size();
        bool dp[n];
        std::memset(dp, 0, sizeof(dp));
        dp[0] = true;

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                // 能從起點跳到 j 且 j 能跳到 i
                if (dp[j] && (j + nums[j]) >= i) {
                    dp[i] = true;
                    break;
                }
            }
        }

        return dp[n - 1];
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501150018328.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501150018328.png)

#### 複雜度分析

令 $n$ 為 `nums` 的長度。

- 時間複雜度： $O(n^2)$

- 空間複雜度： $O(n)$

---

將 `dp` 進一步優化，可以發現到如果 $dp[i] = true$ ， 則 $j = [i, i + nums[i]]$ 範圍的 `dp[j]` 也都會是 `true`，因此 `dp` 陣列會以 `T...T F...F` 的形式存在，這時可以將 `dp` 計算方式從雙迴圈改為單迴圈，並使用一個整數變數 `max_jump` 紀錄當前能夠跳到的**最遠**距離，如果當前 $max\_jump < i$ 表示無法跳到當前位置，return `false`，否則 $max\_jump = \max(max\_jump, i + nums[i])$ ，最後如果能夠跳到所有位置也就能跳到終點，return `true`。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    bool canJump(std::vector<int> &nums) {
        int max_jump = 0, n = nums.size();

        for (int i = 0; i < n; ++i) {
            // 跳不到當前位置，則後面所有位置也都到不了，return false
            if (max_jump < i) {
                return false;
            }
            // 更新 max_jump
            max_jump = std::max(max_jump, nums[i] + i);
        }

        // 每個位置都能到則 return true
        return true;
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501142159769.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501142159769.png)

#### 複雜度分析

令 $n$ 為 `nums` 的長度。

- 時間複雜度： $O(n)$

- 空間複雜度： $O(1)$

### 2. Greedy

從後往前遍歷，對於當前位置，如果找到一個位置 `i` 可以跳到當前位置，則更新當前位置為 `i`，如果有多種就選遍歷時第一次找到的 `i`，令 `i'` 是其他能跳到當前位置的選擇，第一次找到的 `i` 其 index 相較於其他的 `i'` 更大，也就是更靠近終點，三者的 index 關係為： $i' < i < \text{當前位置}$ ，`i'` 一定也能跳到 `i`，所以選擇第一次找到的 `i` 即可。

我們用 `step` 表示現在遍歷到的位置 `i` 和當前位置的距離，如果 `i` 能跳躍的距離 $nums[i] \geq step$ ，則 `i` 可以跳到當前位置，將當前位置改為 `i` 且 $step = 0$ ，反之 $step += 1$ ，繼續找下一個能跳到當前位置的 `i`，最後如果 $step = 0$ 則代表能跳到終點，否則不能跳到終點。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    bool canJump(std::vector<int> &nums) {
        int step = 0, n = nums.size();
        for (int i = n - 2; i >= 0; --i) {
            ++step;
            if (nums[i] >= step) {
                step = 0;
            }
        }

        return step == 0;
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501150014436.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501150014436.png)

#### 複雜度分析

令 $n$ 為 `nums` 的長度。

- 時間複雜度： $O(n)$

- 空間複雜度： $O(1)$
