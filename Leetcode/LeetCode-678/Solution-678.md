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

要判斷一個字串是否為合法的括號字串，可以判斷字串的頭尾字元和中間的字串是否為合法的括號字串。

假設字串 `s` 的長度為 `n`，`dp[i][j]` 表示字串 `s[i:j]` 是否為合法的括號字串，則有：

1. 當子字串長度 = 1，`j - i = 0`，只有 `s' = "*"` 時 `dp[i][i] = true`。
2. 當子字串長度 = 2，`j - i = 1`，只有 `s' = "()" 或 "*)" 或 "(*" 或 "**"` 時 `dp[i][j] = true`。
3. 當子字串長度 > 2，`j - i > 1`，則需要判斷頭尾字元和中間的子字串是否都能構成合法的括號字串，又或者 `dp[i][k] = dp[k+1][j] = true` 的話，則 `dp[i][j] = true`。狀態轉移公式為：

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501131556431.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501131556431.png)

$$
dp[i][j] =
\begin{cases}
\text{true}, & \text{if } (s[i], s[j]) \in \{ ("(", ")"), ("*", ")"), ("(", "*"), ("*", "*") \} \, \text{ and } \, dp[i+1][j-1] = \text{true}, \\[10pt]
\text{true}, & \text{if } \exists k \in [i, j), \ dp[i][k] = \text{true} \, \text{ and } \, dp[k+1][j] = \text{true}, \\[10pt]
\text{false}, & \text{otherwise}.
\end{cases}
$$

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    bool checkValidString(std::string s) {
        int n = s.size();

        // 初始化 dp
        bool dp[n][n];
        for (int i = 0; i < n; ++i) {
            dp[i][i] = s[i] == '*';
        }
        for (int i = 1; i < n; ++i) {
            char c1 = s[i - 1], c2 = s[i];
            dp[i - 1][i] = (c1 == '(' || c1 == '*') && (c2 == ')' || c2 == '*');
        }

        // 從 dp 矩陣的右下角開始，從右往左，從下往上
        // 因為 dp[i][j] 會用到 dp[i + 1][j - 1] 和 dp[i][k] && dp[k + 1][j]
        for (int i = n - 3; i >= 0; --i) {
            for (int j = i + 2; j < n; ++j) {
                dp[i][j] = false;
                if ((s[i] == '(' || s[i] == '*') && (s[j] == ')' || s[j] == '*')) {
                    dp[i][j] = dp[i + 1][j - 1];
                }
                // !dp[i][j] 表示只有 dp[i][j] 為 false 才會進去迴圈來檢查
                for (int k = i; k < j && !dp[i][j]; ++k) {
                    dp[i][j] = dp[i][k] && dp[k + 1][j];
                }
            }
        }

        return dp[0][n - 1];
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501131541466.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501131541466.png)

時間複雜度： $O(n^3)$ ，其中 $n$ 為 `s` 的大小，共要計算 $O(n^2)$ 個狀態，最差情況是每個狀態需要 $O(n)$ 的時間來迭代 $[i, j)$ 區間的狀態檢查 `dp[i][k]` 和 `dp[k + 1][j]`。

空間複雜度： $O(n^2)$ 。
