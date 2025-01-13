# <center> [921. Minimum Add to Make Parentheses Valid](https://leetcode.com/problems/minimum-add-to-make-parentheses-valid/description/) </center>

## 題目敘述

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501131822996.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501131822996.png)

給一個只由 `(`、`)` 組成的字串`s`，請計算出最少需要添加幾個 `(` 和 `)` 才能讓這個字串變成合法的括號字串。

## 解題思路

### 1. Stack

- 遇到 `(` 時，將其推入 stack 中。
- 遇到 `)` 時，如果 stack 不為空，則將 stack 中的 `(` 彈出，若 stack 為空則表示需要添加一個 `(` 才能讓字串變成合法的括號字串，將 `res` + 1。
- 最後回傳答案時，如果 stack 不為空，表示還需要數個 `)` 來滿足沒被匹配到的 `(`，因此回傳 `res + stack.size()` 。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    int minAddToMakeValid(std::string &s) {
        int res = 0;
        std::stack<int> st;
        for (const char &c : s) {
            if (c == '(') {
                st.push(c);
            }
            else if (!st.empty()) {
                st.pop();
            }
            else {
                ++res;
            }
        }

        return res + st.size();
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501131834576.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501131834576.png)

時間複雜度： $O(n)$ ，其中 $n$ 是字串 `s` 的長度。

空間複雜度： $O(n)$ 。

### 2. Greedy

對於方法一，可以將 `stack` 優化成一個整數變數 `balance`，每當遇到 `(` 時 `balance` + 1，遇到 `)` 時 `balance` - 1，當 `balance` < 0 時，表示沒有剩餘的 `(` 能匹配當前 `)`，所以需要增加一個 `(` 來跟 `)`匹配，將 `res + 1`，由於多補了一個 `(` ，因此 `balance` 需要 + 1 變回 0，最後回傳答案時，如果 `balance` > 0，表示有多餘的 `(` 沒有匹配到 `)`，要增加 `)`來跟 `(` 匹配，回傳 `res` + `balance`。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    int minAddToMakeValid(std::string &s) {
        int balance = 0, res = 0;

        for (const char &c : s) {
            balance += c == '(';
            balance -= c == ')';
            if (balance < 0) {
                balance = 0;
                ++res;
            }
        }

        return res + balance;
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501131831811.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501131831811.png)

時間複雜度： $O(n)$ ，其中 $n$ 是字串 `s` 的長度。

空間複雜度： $O(1)$ 。
