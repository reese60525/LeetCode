# <center> [678. Valid Parenthesis String](https://leetcode.com/problems/valid-parenthesis-string/description/) </center>

## 題目敘述

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501131408104.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501131408104.png)

給一個只由 `*`、`(`、`)` 組成的字串 `s`，`*` 可以視為 `(`、`)` 或空字串`""`，請問 `s` 是否為合法的括號字串？

## 解題思路

### 1. Greedy

只要保證在 `s` 中任意一個位置都能滿足以下條件即可認定該字串為合法的括號字串：

- 在任意位置的前綴字串中，`)` 的數量 <= `(` + `*` 的數量。
- 在任意位置的後綴字串中，`(` 的數量 <= `)` + `*` 的數量。

因此我們只要遍歷 `s` 並計算當前位置能否滿足上述條件，若能滿足則回傳 `true`，否則回傳 `false`。

在由左往右遍歷時，若某些 `*` 可能會被改成 `(`，該如何保證它們在由右往左遍歷時不會被改成 `)`？同樣地，若改成 `)`，又如何保證不會在另一方向被改成 `(`？

證明：  

使用矛盾證法，假設一個 `*` 在由左往右遍歷時被當成 `(`，且在由右往左遍歷時被當成 `)`。

1. 在由左往右遍歷時 `*` 被當成 `(`，表示當前的前綴字串中 `)` 數量比 `(` 多，因此需要 `*` 變成 `(` 來平衡，也就代表在 `*` 右邊有多出來的 `)`。

2. 在由右往左遍歷時 `*` 被當成 `)`，表示當前的後綴字串中 `(` 數量比 `)` 多，因此需要 `*` 變成 `)` 來平衡，也就代表在 `*` 左邊有多出來的 `(`。

3. 此時能發現 `*` 在左邊有多出來的 `(`，在右邊有多出來的 `)`，那麼將這兩個匹配就好了啊，`*` 也不用變成 `(` 和 `)` 來保持括號字串的平衡，因此與假設矛盾，可得證 `*` 不可能同時被當成 `(` 和 `)`。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    bool checkValidString(std::string &s) {
        int l_balance = 0, r_balance = 0, n = s.size();

        for (int i = 0; i < n; ++i) {
            // 計算由左往右的括號 balance
            l_balance += s[i] == '*';
            l_balance += s[i] == '(';
            l_balance -= s[i] == ')';
            // 計算由右往左的括號 balance
            r_balance += s[n - i - 1] == '*';
            r_balance += s[n - i - 1] == ')';
            r_balance -= s[n - i - 1] == '(';
            // 如果有任一個無法保持 balance，則該字串不是合法的括號字串
            if (l_balance < 0 || r_balance < 0) {
                return false;
            }
        }

        return true;
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501131416181.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501131416181.png)

時間複雜度： $O(n)$ ，其中 $n$ 為 `s` 的大小。

空間複雜度： $O(1)$ 。

---
同樣使用 Greedy 的解法，但思路稍微不同。考慮到由左至右遍歷可能遇到下列三種情況：

1. 如果遇到 `(` 則未匹配的 `(` 數量 +1。
2. 如果遇到 `)`，需要一個 `(` 來和 `)` 匹配，因此未匹配的 `(` 數量 -1。
3. 如果遇到 `*`，可以將其視為 `(`、`)` 或空字串`""`，因此未匹配的 `(` 數量 -1、+1 或不變。

基於上述三種情況，可以在遍歷的過程中維護未匹配的 `(` 數量的下限 `min` 和上限 `max`。

- 如果遇到 `(`，則 `max + 1`，`min + 1`。
- 如果遇到 `)`，則 `max - 1`，`min - 1`。
- 如果遇到 `*`，則 `max + 1`，`min - 1`。

而 `min` 以及 `max` 的用途分別為：

- `min`：用來計算當 `(` 過多時，判斷 `*` 的數量是否能變成足夠的 `)` 來平衡，如果最後 `min` **大於** 0，則代表 `*` 和 `)` 不夠滿足 `(`，因此該字串不是合法的括號字串，需要注意的是 `min` 可能會變成負數，由於 `*` 可以變成空字串 `""`，所以當 `min` 為負數時，將其設為 0 即可。
- `max`：用來處理當 `)` 過多時，判斷 `*` 的數量是否能變成足夠的 `(` 來平衡，如果最後 `max` **小於** 0，則代表 `*` 和 `(` 不夠滿足 `)`，因此該字串不是合法的括號字串。

由此可見，只有當 `min = 0` 且 `max >= 0` 時，該字串才是合法的括號字串。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    bool checkValidString(std::string &s) {
        int min_l = 0, max_l = 0;
        for (const char &c : s) {
            min_l += c == '(';
            min_l -= c == ')';
            min_l -= c == '*';
            max_l += c == '(';
            max_l -= c == ')';
            max_l += c == '*';
            if (max_l < 0) {
                return false;
            }
            if (min_l < 0) {
                min_l = 0;
            }
        }

        return min_l == 0;
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501131459812.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501131459812.png)

時間複雜度時間複雜度： $O(n)$ ，其中 $n$ 為 `s` 的大小。

空間複雜度： $O(1)$ 。

### 2. Stack

遍歷 `s`，用兩個 stack 分別存放 `(` 和 `*` 的 index，如果遇到 `)` 優先使用 `(` 來匹配，如果 `(` 不夠則使用 `*` 來匹配，如果 `*` 也不夠則代表該字串不是合法的括號字串。

遍歷完後，如果 `(` 的 stack 不為空，則將 `(` 和 `*` 匹配，必須保證在 stack 頂部的 `(` 的 index 要小於 `*` 的 index，否則該字串不是合法的括號字串。例如 `s = "( ( ) * ) ("`，遍歷完後會剩下 `"- - - * - ("`，由於 `(` 右邊沒有 `*` 來匹配，因此該字串不是合法的括號字串。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    bool checkValidString(std::string s) {
        // 記錄左括號和星號的 index，並匹配所有右括號
        std::stack<int> left, star;
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == '(') {
                left.push(i);
            }
            else if (s[i] == '*') {
                star.push(i);
            }
            else {
                if (!left.empty()) {
                    left.pop();
                }
                else if (!star.empty()) {
                    star.pop();
                }
                else {
                    return false;
                }
            }
        }

        // 檢查剩餘的左括號和星號
        while (!left.empty() && !star.empty()) {
            // 如果左括號的 index > 星號的 index，代表左括號右邊沒有星號能匹配
            if (left.top() > star.top()) {
                return false;
            }
            left.pop();
            star.pop();
        }

        // 最後確認左括號是否都已經匹配完
        return left.empty();
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501131503523.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501131503523.png)

時間複雜度： $O(n)$ ，其中 $n$ 為 `s` 的大小。

空間複雜度： $O(n)$ 。

### 3. Dynamic Programming

令 `dp[i][j]` 表示由字串 `s` 的前 `i` 個字元所組成的子字串，是否能跟 `j` 個 `)` 的形成合法括號字串。  
例如有 `s` = "( ( ) ) ( ( ( ( ) )"，則 `dp[7][3]` 表示由字串 `s` 的前 7 個字元所組成的子字串 "( ( ) ) ( ( ("，是否能跟 3 個 `)` 的形成合法括號字串，可以看到該子字串有多出三個 `(` 並且任意位置的 `)` 都能找到一個 `(` 來匹配，因此 `dp[7][3]` 為 `true`。

對於 `dp[i][j]` 的狀態轉移，考慮當前子字串的最後一個字元（`s[i]`），則有以下三種情況：

1. `s[i]` = `(`，則 `dp[i][j] = dp[i-1][j-1]`，因為 `dp[i-1][j-1]` 表示前 `i-1` 個字元組成的子字串，是否能跟 `j-1` 個 `)` 的形成合法括號字串，如果可以，則在其後面加上一個 `(` 後，就能多出一個可以和 `)` 匹配的 `(`，因此變成可以和 `j` 個 `)` 形成合法括號字串，若 `dp[i-1][j-1]` 為 `false`，則在其後面加上一個 `(` 後，也無法和 `j` 個 `)` 形成合法括號字串，因為前 `i-1` 個字元組成的子字串就已經是不合法括號字串了。

2. `s[i]` = `)`，則 `dp[i][j] = dp[i-1][j+1]`，因為 `dp[i-1][j+1]` 表示前 `i-1` 個字元組成的子字串，是否能跟 `j+1` 個 `)` 的形成合法括號字串，如果可以，則在其後面加上一個 `)` 進行匹配後，仍可以和 `j` 個 `)` 形成合法括號字串，若 `dp[i-1][j+1]` 為 `false`，則在其後面加上一個 `)` 後，也無法和 `j` 個 `)` 形成合法括號字串，因為前 `i-1` 個字元組成的子字串就已經是不合法括號字串了。

3. `s[i]` = `*`，由於 `*` 可以是 `(`、`)` 或空字串`""`，因此 `dp[i][j]` 的狀態轉移要考慮三種情況：
    - 將 `*` 視為 `""`，可以匹配的 `)` 數量不變，因此 `dp[i][j] = dp[i-1][j]`。
    - 將 `*` 視為 `(`，則 `dp[i][j] = dp[i-1][j-1]`
    - 將 `*` 視為 `)`，則 `dp[i][j] = dp[i-1][j+1]`。

最後，答案會是 `dp[n][0]`，表示由字串 `s` 的前 `n` 個字元所組成的子字串，是否能跟 0 個 `)` 的形成合法括號字串，也就是 `s` 已經沒有可以匹配的 `)` 時是否為合法的括號字串。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    bool checkValidString(std::string s) {
        int n = s.size();

        // 初始化 dp
        bool dp[n + 1][n + 1];
        std::memset(dp, false, sizeof(dp));
        dp[0][0] = true; // 空字串是合法的括號字串

        for (int i = 1; i <= n; ++i) {
            char c = s[i - 1]; // 前 i 個字元，對應 s[i-1]
            for (int j = 0; j <= i; ++j) {
                if (c == '(' && j > 0) {
                    dp[i][j] = dp[i - 1][j - 1];
                }
                else if (c == ')' && j < i) {
                    dp[i][j] = dp[i - 1][j + 1];
                }
                else if (c == '*') {
                    dp[i][j] = dp[i - 1][j];
                    if (j > 0) {
                        dp[i][j] |= dp[i - 1][j - 1];
                    }
                    if (j < i) {
                        dp[i][j] |= dp[i - 1][j + 1];
                    }
                }
            }
        }

        return dp[n][0];
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501131732158.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501131732158.png)

時間複雜度： $O(n^2)$ ，其中 $n$ 為 `s` 的大小。

空間複雜度： $O(n^2)$ 。

---
由於 `dp[i][j]` 只和 `dp[i-1][]` 有關，因此可以將 `dp` 從二維壓縮成一維，空間複雜度優化為 $O(n)$ 。

需要注意的細節：

- 由於 `j-1`、`j`和`j+1` 這些舊資料都可能會被用到，因此如果是從左往右遍歷，需要用一個變數紀錄 `dp[j-1]`，如果是從右往左遍歷，則需要紀錄 `dp[j+1]`，否則會覆蓋掉舊資料，導致計算錯誤。
- 在原本二維 `dp` 中，當前遍歷到的 `dp[i][j]` 一定是 `false`，但在一維中，當前遍歷到的 `dp[j]` 保存的是上一層的狀態，不一定是 `false`，所以需要一個變數 `cur` 將其設為 false 來代替 `dp[j]` 進行計算，計算完後再將 `cur` 賦值給 `dp[j]`。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    bool checkValidString(std::string s) {
        int n = s.size();

        // 初始化 dp
        bool dp[n + 1];
        std::memset(dp, false, sizeof(dp));
        dp[0] = true; // 空字串是合法的括號字串

        for (int i = 1; i <= n; ++i) {
            char c = s[i - 1]; // 前 i 個字元，對應 s[i-1]
            bool pre;          // 用來紀錄上一層 dp[j-1] 的狀態
            for (int j = 0; j <= i; ++j) {
                // 需要一個變數將其設為 false 來代替 dp[j] 進行計算
                bool cur = false;
                if (c == '(' && j > 0) {
                    cur = pre;
                }
                else if (c == ')' && j < i) {
                    cur = dp[j + 1];
                }
                else if (c == '*') {
                    cur = dp[j];
                    if (j > 0) {
                        cur |= pre;
                    }
                    if (j < i) {
                        cur |= dp[j + 1];
                    }
                }
                pre = dp[j]; // 紀錄上一層 dp[j-1] 的狀態
                dp[j] = cur; // 將 dp[j] 從上一層更新為當前這一層的狀態
            }
        }

        return dp[0];
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501131806356.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501131806356.png)

時間複雜度： $O(n^2)$ ，其中 $n$ 為 `s` 的大小。

空間複雜度： $O(n)$ 。
