# <center> [2116. Check if a Parentheses String Can Be Valid](https://leetcode.com/problems/check-if-a-parentheses-string-can-be-valid/description/) </center>

## 題目敘述

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501121310553.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501121310553.png)

給一組只包含左右括號的字串 `s` 以及一組整包含 `0`、`1` 的字串 `locked`，其中 `locked[i]` 若為 `0` 表示 `s[i]` 的括號可以被替換為 `(` 或是 `)`，`1` 代表該位置的括號不能被替換，請問是否能將 `s` 轉換成合法的括號字串。

合法的括號字串定義為：

- 任意位置的左括號數量 >= 右括號數量
- 整個字串的左括號數量 = 右括號數量

## 解題思路

先說一個小技巧，該題目在傳入 `s` 和 `locked` 時是 pass by value，可以將其改成 pass by reference，這樣跑出來的時間和空間成績比較好看。

```cpp {.line-numbers}
bool canBeValid(std::string s, std::string locked)
// 改成 pass by reference
bool canBeValid(std::string &s, std::string &locked)
```

### 1. Greedy

- 對於 `locked[i]` 為 `0` 的位置，我們可以將其替換為 `(` 或 `)`，因此我們可以將其視為 `*` 表示為任意括號。

- 對於 `locked[i]` 為 `1` 的位置，我們無法替換其括號，因此必須保證該位置的括號都能找到能夠匹配的括號。

首先先處理 `locked[i] = 1` 的 `)`，將除了 `)` 以外的括號都看作 `(`，而 `(` 又能分成 `locked[i] = 0` 和 `locked[i] = 1` 兩種情況，而最好的匹配方式是優先將 `locked[i] = 1` 的 `(` 和 `)` 匹配，若沒有 `locked[i] = 1` 的 `(` 則匹配 `locked[i] = 0` 的 `(`，若都沒有則代表無法滿足 `locked[i] = 1` 的 `)` 的匹配，該字串無法轉換成合法的括號字串。  

將 `locked[i] = 1` 的 `)` 都處理完後，此時尚未匹配的只剩下 `locked[i] = 1` 的 `(` 和 `locked[i] = 0` 的 `()`，而 `locked[i] = 0` 的 `()` 可以任意替換為 `(` 或 `)`，因此只要所有 `locked[i] = 1` 的 `(` 能夠在其右邊找到 `locked[i] = 0` 的 `()` 進行匹配，則該字串就可以轉換成合法的括號字串。

基於上述分析，我們可以得出以下演算法：  

1. 檢查 `s` 的大小，若 `s` 的大小為奇數，則回傳 `false`。

2. 遍歷 `s` 並用兩個 `stack` 分別儲存 `locked[i] = 0` 的 `()` 的 index 以及 `locked[i] = 1` 的 `(` 的 index，然後和 `locked[i] = 1` 的 `)` 進行匹配，若 `locked[i] = 1` 的 `)` 沒有可以匹配的括號則回傳 `false`。

3. 遍歷完 `s` 後，將兩個 `stack` 中的頂部 element 比較在 `s` 中的 index 大小，若 `locked[i] = 1` 的 index 比 `locked[i] = 0` 的 index 大，則代表該 `locked[i] = 1` 的 `(` 在其右方找不到能匹配的括號，回傳 `false`。

4. 最後檢查 `locked[i] = 1` 的 `stack` 是否為空，若為空則代表所有 `locked[i] = 1` 的 `(` 都能找到能匹配的括號，而剩下的 `locked[i] = 0` 的括號都能隨意轉換來互相匹配，因此回傳 `true`，否則回傳 `false`。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    bool canBeValid(std::string &s, std::string &locked) {
        // 奇數個括號不可能有合法的括號字串，回傳 false
        if (s.size() & 1) {
            return false;
        }

        // 處理 locked[i] = 1 的左括號
        std::stack<int> st_unlocked, st_locked;
        for (int i = 0; i < s.size(); ++i) {
            if (locked[i] == '0') {
                st_unlocked.push(i);
            }
            else if (s[i] == '(') {
                st_locked.push(i);
            }
            else {
                if (!st_locked.empty()) {
                    st_locked.pop();
                }
                else if (!st_unlocked.empty()) {
                    st_unlocked.pop();
                }
                else {
                    return false;
                }
            }
        }

        // 處理 locked[i] = 1 的右括號
        while (!st_locked.empty() && !st_unlocked.empty()) {
            // locked[i] = 1 的右括號必須在 locked[i] = 0 的括號之後才能匹配
            if (st_locked.top() > st_unlocked.top()) {
                return false;
            }
            st_locked.pop();
            st_unlocked.pop();
        }

        // 若 st_locked 還有剩下，表示無法將 locked[i] = 1 的左括號全都匹配，回傳 false
        // 反之 st_locked 為空，則剩下的 locked[i] = 0 的括號能夠互相匹配，回傳 true
        return st_locked.size() == 0;
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501121446585.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501121446585.png)

時間複雜度： $O(n)$ ，其中 $n$ 為 `s` 的大小。

空間複雜度： $O(n)$ 。

---

上述的解法還能進一步優化空間複雜度，我們只要保證在 `s` 中任意一個位置都能滿足以下條件即可認定該字串為合法的括號字串：

- 在任意位置的前綴字串中，`locked[i] = 1` 的 `)` 數量 <= `(` 數量 + `locked[i] = 0` 的 `)` 數量。
- 在任意位置的後綴字串中，`locked[i] = 1` 的 `(` 數量 <= `)` 數量 + `locked[i] = 0` 的 `(` 數量。

因此我們只要遍歷 `s` 並計算當前位置能否滿足上述條件，若能滿足則回傳 `true`，否則回傳 `false`。

在由左往右遍歷時，若某些 `locked[i] = 0` 的括號被改成 `(`，該如何保證它們在由右往左遍歷時不會被改回 `(`？同樣地，若改成`)`，又如何保證不會在另一方向被改回`)`？

證明：  

**必要前提：所有括號都會優先和 `locked[i] = 1` 的括號匹配，若 `locked[i] = 1` 的括號不夠，才會和 `locked[i] = 0` 的括號匹配。**

使用矛盾證法，假設一個 `locked[i] = 0` 的括號 `*` 在由左往右遍歷時被當成 `(`，且在由右往左遍歷時被當成 `)`。

1. 在由左往右遍歷時 `*` 被當成 `(`，表示當前的前綴字串中 `locked[i] = 1` 的 `)` 數量比 `(` 多，因此需要 `*` 變成 `(` 來平衡，也就代表在 `*` 右邊有多出來的 `)`。

2. 在由右往左遍歷時 `*` 被當成 `)`，表示當前的後綴字串中 `locked[i] = 1` 的 `(` 數量比 `)` 多，因此需要 `*` 變成 `)` 來平衡，也就代表在 `*` 左邊有多出來的 `(`。

3. 此時能發現 `*` 在左邊有多出來的 `(`，在右邊有多出來的 `)`，那麼將這兩個匹配就好了啊，`*` 也不用變成 `(` 和 `)` 來保持括號字串的平衡，因此與假設矛盾，可得證 `*` 不可能同時被當成 `(` 和 `)`。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    bool canBeValid(std::string &s, std::string &locked) {
        // 奇數個括號不可能有合法的括號字串，回傳 false
        int n = s.size();
        if (s.size() & 1) {
            return false;
        }

        // 檢查 locked[i] = 1 的左右括號是否能滿足當前 substring 的括號平衡
        int l_balance = 0, r_balance = 0;
        for (int i = 0; i < n; ++i) {
            l_balance += (s[i] == ')' && locked[i] == '1') ? -1 : 1;
            r_balance += (s[n - i - 1] == '(' && locked[n - i - 1] == '1') ? -1 : 1;
            // 如果當前 substring 的括號不平衡，回傳 false
            if (l_balance < 0 || r_balance < 0) {
                return false;
            }
        }

        return true;
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501121443072.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501121443072.png)

時間複雜度： $O(n)$ ，其中 $n$ 為 `s` 的大小。

空間複雜度： $O(1)$ 。
