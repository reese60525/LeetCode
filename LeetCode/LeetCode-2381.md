# <center> [2381. Shifting Letters II](https://leetcode.com/problems/shifting-letters-ii/description/) </center>

## 題目敘述

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures202501051051405.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures202501051051405.png)

給一個由小寫字母組成的字串 `s` 以及二維整數陣列 `shifts`，`shifts[i] = [start_index, end_index, direction]`，若 `direction` 為 0 則表示將 `s[start_index]` 到 `s[end_index]` 的字母都用字母表中的前一個字母來取代，若 `direction` 為 1 則表示將 `s[start_index]` 到 `s[end_index]` 的字母都用字母表中的下一個字母取代，字母表視為一個循環，也就是 `z` 的下一個字母為 `a`，`a` 的前一個字母為 `z`，回傳執行完所有 `shifts` 後的 `s`。

## 解題思路

### 1. Difference Array and Prefix Sum

創建一個長度為 `s.size() + 1` 的 `diff` 陣列，`diff[i]` 表示從 `s[i]` 開始要位移的量，比如有一個 `shift` 為 [st, ed, 0]，表示要將 `s[st]` 到 `s[ed]` 的字母都用字母表中的前一個字母來取代，那麼 `diff[st]` 要加 -1，`diff[ed+1]` 要加 1，因此當我們要計算 `s[st]` 的位移量時，只要將 `diff[0]` 到 `diff[st]` 的值全部加起來就會是 `s[i]` 的位移量，並且 `s[st]` 到 `s[ed]` 這部分的字母也都能受到 `diff[st]` 的影響，在 $index = [st,ed]$ 這段區間的字母做完位移後，會在 `diff[ed+1]` 將 `shift = [st, ed, 0]` 的位移影響給消除掉。

因此我們可以先遍歷 `shifts`，計算 `diff` 陣列的值，接著再遍歷 `s`，同時累加 `diff[i]`，而 `s[i]` 的位移量就是累加的 `diff` 的值，最後回傳位移後 `s` 即可。

e.g.

`s` = "abc"，`shifts` = {{0, 1, 0}, {1, 2, 1}, {0, 2, 1}}

- 先計算 `diff` 陣列

    ```text
    index： 0  1  2  3
    shift：-1     1
    　         1    -1
        　  1       -1
    diff：  0  1  1 -2
    ```

- 遍歷 `s`，同時累加 `diff` 的值

  - 累加 diff = 0 + 0 = 0，`s[0]` 要位移 0 個單位

  - 累加 diff = 0 + 1 = 1，`s[1]` 要位移 1 個單位

  - 累加 diff = 1 + 1 = 2，`s[2]` 要位移 2 個單位

- 最終 `s` 會變成 "ace"。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    std::string shiftingLetters(std::string s, std::vector<std::vector<int>> &shifts) {
        // 遍歷 shifts，計算 diff
        int diff[s.size() + 1];
        std::memset(diff, 0, sizeof(diff));
        for (auto &shift : shifts) {
            int st = shift[0], ed = shift[1], op = shift[2];
            diff[st] += op ? 1 : -1;
            diff[ed + 1] += op ? -1 : 1;
        }

        // 遍歷 s 來計算每個字元的位移量
        int total_diff = 0;
        for (int i = 0; i < s.size(); ++i) {
            total_diff += diff[i];
            int k = s[i] - 'a';
            // 若 k 位移後是負數，則 mod 後要取正
            s[i] = ((k + total_diff) % 26 + 26) % 26 + 'a';
        }

        return s;
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures202501051125140.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures202501051125140.png)

#### 複雜度分析

令 $n$ 為 `s` 的長度， $m$ 為 `shifts` 的長度。

- 時間複雜度： $O(n + m)$

- 空間複雜度： $O(n)$
