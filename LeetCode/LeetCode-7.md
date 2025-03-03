# <center> [7. Reverse Integer](https://leetcode.com/problems/reverse-integer/description/) </center>

## 題目敘述

[![](https://i.imgur.com/MaCqdkQ.png)](https://i.imgur.com/MaCqdkQ.png)

給一個整數 `x`，將其反轉後回傳，如果反轉後的數會 overflow 則回傳 0。

**不可以使用超過 32 bit 的變數來計算。**

## 解題思路

### 1. Bit Manipulation

`x` 的反轉數 `x'` 計算方式： $x' = x' \cdot 10 + x \mod 10$

由於不能使用超過 32 bits 的變數來計算，因此當 `x'` overflow 時會報錯，所以要在計算過程中預先判斷 `x'` 是否 overflow。

可以透過這個公式： $x' \cdot 10 + x \mod 10 > INTMAX$ 來判斷會不會 overflow，但由於 `x'` 是 32 bits 整數，若計算後的結果會 overflow 則 $x' \cdot 10$ 也會因為 overflow 而報錯，可以將這個公式交換處理後變成 $x' > \frac{INTMAX - x \mod 10}{10}$ ，這樣就能在判斷 `x'` 是否 overflow 的同時也不會因為 overflow 而報錯。

整體的計算流程如下，因為 `x` 可以是正數或是負數，為了方便計算，先用 `sign` 來記錄 `x` 的正負號，由於 `INT_MIN` 轉正數會 overflow，所以一律將 `x` 轉成負數來計算 `x'`，最後再根據 `sign` 決定回傳值的正負號。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    int reverse(int x) {
        // 紀錄正負號並將 x 一律轉為負數，因為 INT_MIN 轉正數會 overflow
        bool sign = true;
        if (x > 0) {
            sign = false;
            x *= -1;
        }

        int res = 0;
        while (x != 0) {
            // 判斷 res 是否會 overflow
            if (res < (INT_MIN - x % 10) / 10) {
                return 0;
            }
            res = res * 10 + x % 10;
            x /= 10;
        }

        // 根據輸入的正負號來輸出答案
        return (sign == 1) ? res : -res;
    }
};
```

[![](https://i.imgur.com/zOfgep9.png)](https://i.imgur.com/zOfgep9.png)

#### 複雜度分析

- 時間複雜度： $O(\lfloor log_{10}|x| \rfloor + 1)$

- 空間複雜度： $O(1)$

---

第二種做法和第一種類似，但判斷條件稍微不同，並且不需要做正負號的轉換，更簡潔易懂。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    int reverse(int x) {
        int res = 0;
        while (x != 0) {
            // 判斷正數是否會 overflow
            if (res > INT_MAX / 10 || (res == INT_MAX / 10 && x % 10 > 7)) {
                return 0;
            }
            // 判斷負數是否會 overflow
            if (res < INT_MIN / 10 || (res == INT_MIN / 10 && x % 10 < -8)) {
                return 0;
            }

            res = res * 10 + x % 10;
            x /= 10;
        }

        return res;
    }
};
```

[![](https://i.imgur.com/HjTN0NP.png)](https://i.imgur.com/HjTN0NP.png)

#### 複雜度分析

- 時間複雜度： $O(\lfloor log_{10}|x| \rfloor + 1)$

- 空間複雜度： $O(1)$
