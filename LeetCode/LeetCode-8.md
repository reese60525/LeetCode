# <center> [8. String to Integer (atoi)](https://leetcode.com/problems/string-to-integer-atoi/description/) </center>

## 題目敘述

[![](https://i.imgur.com/u1InTaC.png)](https://i.imgur.com/u1InTaC.png)

請實現 `atoi` 這個函式，用於將字串轉換成整數，`atoi` 有以下五個規則：

1. 忽略開頭的空白字元 `' '`。

   - `"    123"` -> `123`

   - `"   23   12"` -> `23`

2. 若遇到`'+'`，輸出的數字為正數，若遇到`'-'`，輸出的數字為負數，若都沒有則預設為正數。

   - `"   -123"` -> `-123`

   - `"-  42"` -> `0`

   - `"+00013"` -> `13`

3. 忽略所有前導 `0`，直到遇到**非數字字元**或是字串結束為止，如果沒有讀取到任何數字則回傳 `0`。

   - `"-00032"` -> `-32`

   - `"-0330 032"` -> `-330`

4. 若數字超過 32 位元有符號整數範圍 `[-2^31, 2^31 - 1]`，則回傳 `INT_MAX` 或 `INT_MIN`。

   - `" -00999999123444"` -> `INT_MIN`

5. 若是遇到非數字字元，則停止讀取數字。

   - `"   -00032a"` -> `-32`

   - `"  -A32S"` -> `0`

   - `"  32 1"` -> `32`

## 解題思路

### 1. IF ELSE

就照著題目敘述的五個規則，一個一個判斷，並且記錄正負號，最後再轉換成整數。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    int myAtoi(std::string &s) {
        int i = 0, n = s.size(), sign = 1;

        // 處理前導空白
        while (i < n && s[i] == ' ') {
            ++i;
        }
        // 判斷正負號
        if (i < n && (s[i] == '+' || s[i] == '-')) {
            sign = (s[i++] == '+') ? 1 : -1;
        }
        // 處理數字
        int res = 0;
        while (i < n && s[i] - '0' >= 0 && s[i] - '0' <= 9) {
            int temp = s[i] - '0';
            // 判斷是否 overflow
            if (res > (INT_MAX - temp) / 10) {
                return (sign == 1) ? INT_MAX : INT_MIN;
            }
            res = res * 10 + temp;
            ++i;
        }
        return res * sign;
    }
};
```

[![](https://i.imgur.com/GyaFAEk.png)](https://i.imgur.com/GyaFAEk.png)

#### 複雜度分析

令 $n$ 為字串 `s` 的長度。

- 時間複雜度： $O(n)$

- 空間複雜度： $O(1)$

### 2. Deterministic Finite Automaton（DFA）

建立一個確定狀態的有限自動機，在每一個時刻都會有一個狀態，並且根據當前輸入進來的字元來決定下一個狀態，根據題目給的條件可以建立如下圖的 DFA：

[![](https://i.imgur.com/wCMdmhQ.png)](https://i.imgur.com/wCMdmhQ.png)

將上圖的 DFA 狀態以圖表呈現：

| 狀態       | 空白鍵 `' '`  | 正負號 `'+'` 或 `'-'`  | 數字 `'0'~'9'`  | 其他字元  |
| --------- | ------------ | --------------------- | -------------- | -------- |
| start     | start        | sign                  | in_number      | end      |
| sign      | end          | end                   | in_number      | end      |
| in_number | end          | end                   | in_number      | end      |
| end       | end          | end                   | end            | end      |

藉由這個圖表就可以寫出 DFA 的程式碼。

#### 程式碼

```cpp {.line-numbers}
class DFA {
  private:
    std::string state = "start";
    // 狀態轉移表
    const std::unordered_map<std::string, std::vector<std::string>> table {
        {"start",     {"start", "signed", "in_number", "end"}},
        {"signed",    {"end", "end", "in_number", "end"}     },
        {"in_number", {"end", "end", "in_number", "end"}     },
        {"end",       {"end", "end", "end", "end"}           }
    };

    // 根據輸入字元，取得狀態轉移表的欄位
    int getCol(const char &c) {
        if (c == ' ') {
            return 0;
        }
        else if (c == '+' || c == '-') {
            return 1;
        }
        else if (isdigit(c)) {
            return 2;
        }
        else {
            return 3;
        }
    }

  public:
    int sign = 1, res = 0;

    // 根據狀態來執行不同任務
    void get(const char &c) {
        state = table.at(state)[getCol(c)];
        if (state == "signed") {
            sign = (c == '+') ? 1 : -1;
        }
        else if (state == "in_number") {
            if (res > (INT_MAX - (c - '0')) / 10) {
                res = (sign == 1) ? INT_MAX : INT_MIN;
                sign = 1; // 避免 INT_MIN 被轉成正數
                state = "end";
                return;
            }
            res = res * 10 + (c - '0');
        }
    }

    std::string getState() {
        return state;
    }

    int getRes() {
        return res * sign;
    }
};

class Solution {
  public:
    int myAtoi(std::string &s) {
        DFA dfa;
        for (const char &c : s) {
            if (dfa.getState() == "end") {
                break;
            }
            dfa.get(c);
        }

        return dfa.getRes();
    }
};
```

[![](https://i.imgur.com/3Zvfbpt.png)](https://i.imgur.com/3Zvfbpt.png)

#### 複雜度分析

令 $n$ 為字串 `s` 的長度。

- 時間複雜度： $O(n)$

- 空間複雜度： $O(1)$
