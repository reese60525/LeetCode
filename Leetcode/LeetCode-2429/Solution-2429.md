# <center> [2429. Minimize XOR](https://leetcode.com/problems/minimize-xor/description/) </center>

## 題目敘述

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501151157200.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501151157200.png)

給兩個正整數 `num1` 和 `num2`，令 `n2` 表示 `num2` 的二進位表示法中 `1` 的數量，請找出一個正整數 `x` 其二進位表示法中 `1` 的數量 = `n2`，且 `x XOR num1` 的值要是最小的。

## 解題思路

### 1. Greedy and Bit Manipulation

想要讓 `x XOR num1` 的值最小，代表要讓 `num1` 的二進位表示法中**高位數**的 `1` 的數量要盡可能的少，用以下的例子來解釋：

`num1` = 0x53 = 0b110101，`num2` = 0x13 = 0b001101  

- 先計算出 `num2` 的二進位表示法中 `1` 的數量 `n2` = 3，因此 `x` 的二進位表示法中 `1` 的數量也要是 3。
- 接著想要讓 `x XOR num1` 的值最小，可以將 `num1` 中 bit 為 1 的高位數 bit 和 `x` 的 1 進行 `XOR` 運算使該 bit 變成 0，因此 `x` 的 1 要從 `num1` 的最高位依序對應到 value = 1 的 bit，如下所示：

    ```text
    num1     = 0b110101
    x        = 0b110100
    x ^ num1 = 0b000001
    ```

- 最後，假如 `n2` 大於 `num1` 二進位表示法中 `1` 的數量 `n1`，那麼把 `num1` 的 1 都變為 0 之後 `x` 還會有剩下的 1 要填入，所以要將 `x` 從最第低位依序把 value = 0 的 bit 改為 1。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    int minimizeXor(int &num1, int &num2) {
        // 計算 num2 中 bit = 1 的數量
        int cnt = std::popcount(static_cast<unsigned int>(num2));
        // 計算 num1 中 bit = 1 的最高位置，例如 0b1101101 的最高位 1 在第 7 bit
        int high = std::bit_width(static_cast<unsigned int>(num1));

        // 將 1 填入 x，填入的位置從最高位依序對應到 num1 中 1 的 位置
        int res = 0;
        while (high-- > 0) {
            res <<= 1;
            // 確認是否還有 1 要填入 x 以及當前 num1 的 bit 是不是 1
            if (cnt > 0 && num1 & (1 << high)) {
                ++res;
                --cnt;
            }
        }

        // 將剩下的 1 從最低位依序填入 x
        int flag = 1;
        while (cnt > 0) {
            // 確認當前 x 的 bit 是不是 0，0 的話可以填入 1
            if (!(res & flag)) {
                res |= flag;
                --cnt;
            }
            flag <<= 1;
        }

        return res;
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501151307331.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501151307331.png)

時間複雜度： $O(\log n)$ ，其中 $n$ 是 `max(num1, num2)`。

空間複雜度： $O(1)$ 。

---

我們可以反向思考，令 `n1` 和 `n2` 分別表示 `num1` 和 `num2` 的二進位表示法中 `1` 的數量，由於 `x` 的 `n2` 個 1 都會和 `num1` 的高位數 1 在相同的位置，分別以下三種情況：

- `n1` = `n2`：此時 `x = num1`，因此 `num1` 就是答案。

- `n1` > `n2`：將 `n2` 個 1 都填入 `x` 後，`num1` 中剩下的未被對應到的 1 在 `x` 都會是 0，因此只要從 `num1` 最低位開始，將 `n1 - n2` 個 0 取代原本是 1 的 bit 就會得到 `x`。

    例如：`num1` = 0x53 = 0b110101，`num2` = 0x5 = 0b000101

    ```text
    num1     = 0b110101
    x        = 0b110000
    x ^ num1 = 0b000101

- `n1` < `n2`：將 `n1` 個 1 都填入 `x` 後，此時 `x = num1`，並且還有 `n2 - n1` 個 1 要填入 `x` 中，這些 1 會從 `x` 的最低位開始依序將原本是 0 的 bit 變成 1，因此只要從 `num1` 的最低位開始，將 `n2 - n1` 個 0 取代原本是 1 的 bit 就會得到 `x`。

    例如：`num1` = 0x149 = 0b10010101，`num2` = 0x63 = 0b00111111

    ```text
    num1     = 0b10010101
    x        = 0b10011111
    x ^ num1 = 0b00001010
    ```

而要將某個數 `n` 的最低位 1 變成 0 或是 0 變成 1，可以透過以下的技巧：

- 最低位 1 變成 0：`n & (n - 1)`，`n - 1` 可以讓 `n` 的最低位 1 變成 0，並且將其後面的 0 變成 1，例如：

    ```text
    n           = 0b1011000
    n - 1       = 0b1010111
    n & (n - 1) = 0b1010000
    ```

- 最低位 0 變成 1：`n | (n + 1)`，`n + 1` 可以讓 `n` 的最低位 0 變成 1，並且將其後面的 1 變成 0，例如：

    ```text
    n           = 0b1000111
    n + 1       = 0b1001000
    n | (n + 1) = 0b1001111
    ```

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    int minimizeXor(int &num1, int &num2) {
        // 計算 num1 中 bit = 1 的數量
        int n1 = std::popcount(static_cast<unsigned int>(num1));
        // 計算 num2 中 bit = 1 的數量
        int n2 = std::popcount(static_cast<unsigned int>(num2));

        for (; n1 > n2; --n1) {
            num1 &= num1 - 1;
        }
        for (; n2 > n1; --n2) {
            num1 |= num1 + 1;
        }

        return num1;
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501151306766.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501151306766.png)

時間複雜度： $O(\log n)$ ，其中 $n$ 是 `max(num1, num2)`。

空間複雜度： $O(1)$ 。
