# <center> [1541. Minimum Insertions to Balance a Parentheses String](https://leetcode.com/problems/minimum-insertions-to-balance-a-parentheses-string/description/) </center>

## 題目敘述

[![](https://i.imgur.com/Su1U0ps.png)](https://i.imgur.com/Su1U0ps.png)

給一個由 `(` 和 `)` 組成的字串 `s`，每一個 `(` 需要有對應的 `))` 來組成合法的括號字串，對於 `s` 可以插入任意數量的 `(` 和 `)` 來讓 `s` 變成合法的括號字串，求最少需要插入幾個字元。

## 解題思路

### 1. Greedy

這題就只不過是把一般常見的一個 `(` 配對一個 `)` 變成配對 `))` 而已，稍微更改一下邏輯即可。

令 `left` 為可使用的 `(` 數量，`res` 為需要插入的字元數量，遍歷 `s`，考慮到以下三種情況：

1. 當前字元為 `(`，則 $left + 1$ 。

2. 當前字元為 `)`，且下個字元也是 `)`

   - 如果 $left > 0$ ，則可以配對， $left - 1$ 。

   - 如果 $left = 0$ ，則需要插入一個 `(` 來完成配對， $res + 1$ 。

3. 當前字元為 `)`，且下個字元不是 `)`

   - 如果 $left > 0$ ，則需要插入一個 `)` 來完成配對， $res + 1$ 。

   - 如果 $left = 0$ ，則需要插入一個 `(` 和一個 `)` 來完成配對， $res + 2$ 。

結束遍歷後，如果 $left > 0$ ，則需要插入 `left` 個 `))` 來完成配對，因此答案為 $res + left \times 2$ 。

#### 程式碼

```cpp {.lline-numbers}
class Solution {
  public:
    int minInsertions(std::string &s) {
        int left = 0, res = 0, n = s.size();
        for (int i = 0; i < n; ++i) {
            if (s[i] == '(') {
                ++left;
            }
            else {
                (i < n - 1 && s[i + 1] == ')') ? ++i : ++res;
                (left == 0) ? ++res : --left;
            }
        }

        return res + left * 2;
    }
};
```

[![](https://i.imgur.com/YEVOq7d.png)](https://i.imgur.com/YEVOq7d.png)

#### 複雜度分析

令 $n$ 為 `s` 的長度。

- 時間複雜度： $O(n)$

- 空間複雜度： $O(1)$
