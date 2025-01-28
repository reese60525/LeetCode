# <center> [1963. Minimum Number of Swaps to Make the String Balanced](https://leetcode.com/problems/minimum-number-of-swaps-to-make-the-string-balanced/description/) </center>

## 題目敘述

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501140940848.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501140940848.png)

給一個只由 `[` 和 `]` 組成的字串 `s`，`s` 中的 `[` 和 `]` 數量相同，且 `s` 長度為偶數，可以對 `s` 中的 element 進行交換的操作，請問最少需要交換幾次才能讓 `s` 變成合法的括號字串。

## 解題思路

### 1. Greedy

遍歷 `s`，當遇到 `[` 時 $balance + 1$ 表示當前有多少個 `[` 可以拿來和 `]` 匹配，當遇到 `]` 時 將其和 `[` 匹配，因此 $balance - 1$ ，要是過程中 $balance < 0$ 則將其設為 0。

遍歷完後如果有括號沒被配對到，那必定是兩兩一組，並且形式為 `]...][...[`，而 `balance` 就是沒被配對到的 `[` 數量，讓我們來觀察以下幾種情況

- 剩 1 組沒被配對到 `][`，將 s[0] 和 s[1] 交換，需要交換 1 次變成 `[]`

- 剩 2 組沒被配對到 `]][[`，將 s[0] 和 s[3] 交換，需要交換 1 次變成 `[][]`

- 剩 3 組沒被配對到 `]]][[[`，將 s[0] 和 s[5]、s[2] 和 s[3] 交換，需要交換 2 次變成 `[][][]`

- 剩 4 組沒被配對到 `]]]][[[[`，將 s[0] 和 s[7]、s[2] 和 s[5] 交換，需要交換 2 次變成 `[][][][]`

- 剩 5 組沒被配對到 `]]]]][[[[[`，將 s[0] 和 s[9]、s[2] 和 s[7]、s[4] 和 s[5] 交換，需要交換 3 次變成 `[][][][][]`

- 剩 6 組沒被配對到 `]]]]][[[[[[`，將 s[0] 和 s[11]、s[2] 和 s[9]、s[4] 和 s[7] 交換，需要交換 3 次變成 `[][][][][][]`

- ...以此類推

可以發現，當有 `balance` 組沒被配對到，我們需要交換 $\frac{balance + 1}{2}$ 次。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    int minSwaps(std::string &s) {
        int balance = 0;

        for (const char &c : s) {
            (c == '[') ? ++balance : --balance;
            balance = (balance < 0) ? 0 : balance;
        }

        return (balance + 1) >> 1;
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501141003494.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501141003494.png)

#### 複雜度分析

令 $n$ 為 `s` 的長度。

- 時間複雜度： $O(n)$

- 空間複雜度： $O(1)$
