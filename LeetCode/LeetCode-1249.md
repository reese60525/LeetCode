# <center> [1249. Minimum Remove to Make Valid Parentheses](https://leetcode.com/problems/minimum-remove-to-make-valid-parentheses/description/) </center>

## 題目敘述

[![](https://i.imgur.com/SNnznIL.png)](https://i.imgur.com/SNnznIL.png)

給一個由小寫英文字母和 `(` 、 `)` 組成的字串 `s`，請刪除最少的字元，使得字串變成合法的括號字串，並回傳刪除後的字串。

## 解題思路

### 1. Stack

遍歷 `s`，遇到 `(` 時將其 index 存入 stack，遇到 `)` 時，若 stack 為空，則把 `)` 從 `s` 中刪除，否則將 stack 頂部 element pop。最後再將 stack 中剩下的 `(` 從 `s` 中刪除。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    std::string minRemoveToMakeValid(std::string &s) {
        // 紀錄要刪除的左括號所在位置 index
        std::stack<int> left;
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == '(') {
                left.push(i);
            }
            else if (s[i] == ')') {
                // 當前右括號沒有可以匹配的左括號，將其刪除
                if (left.empty()) {
                    s.erase(s.begin() + i);
                    // 刪除當前位置的字元後，會將後面沒遍歷到的字元補過來
                    // 因此需要將 i - 1，下一輪再 check 一次
                    --i;
                }
                else {
                    left.pop();
                }
            }
        }

        // 刪除多餘的左括號
        while (!left.empty()) {
            s.erase(s.begin() + left.top());
            left.pop();
        }

        return s;
    }
};
```

[![](https://i.imgur.com/dI7oJrT.png)](https://i.imgur.com/dI7oJrT.png)

#### 複雜度分析

令 $n$ 為 `s` 的長度。

- 時間複雜度： $O(n)$

- 空間複雜度： $O(n)$

### 2. Greedy

先從左往右遍歷 `s`，當遇到多餘的右括號時，將其刪除，接著從右往左遍歷 `s`，當遇到多餘的左括號時，將其刪除，最後回傳刪除後的字串。

#### 程式碼

```cpp {.line-numbers}
class Solution {
public:
    string minRemoveToMakeValid(string& s) {
        int balance = 0;

        // 從左往右遍歷，將多餘的右括號刪除
        for (int i = 0; i < s.size(); ++i) {
            balance += s[i] == '(';
            balance -= s[i] == ')';
            if (balance < 0) {
                balance = 0;
                s.erase(s.begin() + i);
                --i;
            }
        }

        // 從右往左遍歷，將多餘的左括號刪除
        balance = 0;
        for (int i = s.size() - 1; i >= 0; --i) {
            balance += s[i] == ')';
            balance -= s[i] == '(';
            if (balance < 0) {
                balance = 0;
                s.erase(s.begin() + i);
            }
        }

        return s;
    }
};
```

[![](https://i.imgur.com/L1rX85e.png)](https://i.imgur.com/L1rX85e.png)

#### 複雜度分析

令 $n$ 為 `s` 的長度。

- 時間複雜度： $O(n)$

- 空間複雜度： $O(1)$
