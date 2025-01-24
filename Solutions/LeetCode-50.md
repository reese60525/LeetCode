# <center> [LeetCode - 50. Pow(x, n)](https://leetcode.com/problems/powx-n/description/) </center>

## 題目敘述

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures202412160815457.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures202412160815457.png)

實現 `std::pow(x,n)` 函式。

e.g.

1. $pow(2,10) = 1024$

2. $pow(3,-2) = \frac{1}{9} \approx 0.111111111$

## 解題思路

### 1. Divide and Conquer and Tail Recursion

最簡單的辦法就是遞迴，每遞迴一次就將 `n` 減 1 並且乘 1 次 `x`，直到 $n = 0$ 為止，雖然時間複雜度是 $O(n)$ ，但當 $n = 2^{31}$ 時這樣的執行速度就太慢了。

因此可以用 divide and conquer 的方式來加速，遞迴公式為: $pow(x,\frac{n}{2}) \cdot pow(x,n - \frac{n}{2})$ ，這樣就可以將時間複雜度降低到 $O(\log n)$ ，但這樣的寫法因為遞迴深度過深仍會 TLE，並且可能會 stack overflow，因此需要用 tail recursion 來解決。

當 `n` 為偶數時， $x^n = x^{\frac{n}{2}} \cdot x^{\frac{n}{2}} = {x^{2\cdot{\frac{n}{2}}}}$ ，當 `n` 為奇數時， $x^n = x^{\frac{n}{2}} \cdot x^{\frac{n}{2}} \cdot x$ 。令 `res` 為答案，當 `n` 為偶數時， 將 `x` 平方，如果 `n` 為奇數時，除了要把 `x` 平方還要將多出來的 `x` 再乘給 `sum` ， `n` 最後一定會變成 1 ，會將所有 `x` 累積乘給 `sum`，最後回傳 `sum` 即可。

e.g.

1. $x = 2$ ， $n = 7$ ， $sum = 1$

    - $pow(2,7)$ ， $x = x^2 = 4$ ， $n = \frac{n}{2} = 3$ ， `sum` 乘以原本的 `x`， $sum = 2$

    - $pow(4,3)$ ， $x = x^2 = 16$ ， $n = \frac{n}{2} = 1$ ， `sum` 乘以原本的 `x`， $sum = 8$

    - $pow(16,1)$ ， $x = x^2 = 256$ ， $n = \frac{n}{2} = 0$ ， `sum` 乘以原本的 `x`， $sum = 128$

    - $pow(256,0)$ ， $n = 0$ ， return $sum = 128$

2. $x = 2$ ， $n = 6$ ， $sum = 1$

    - $pow(2,6)$ ， $x = x^2 = 4$ ， $n = \frac{n}{2} = 3$ ，因為 `n` 為偶數所以 `sum` 不變

    - $pow(4,3)$ ， $x = x^2 = 16$ ， $n = \frac{n}{2} = 1$ ， `sum` 乘以原本的 `x`， $sum = 4$

    - $pow(16,1)$ ， $x = x^2 = 256$ ， $n = \frac{n}{2} = 0$ ， `sum` 乘以原本的 `x`， $sum = 64$

    - $pow(256,0)$ ， $n = 0$ ， return $sum = 64$

利用這樣的方式就能將普通遞迴改成尾遞迴，避免了 stack overflow 的問題。

#### 程式碼

```c++ {.line-numbers}
class Solution {
  public:
    // sum 用於儲存 n 為奇數時多出來的 x，由於最後 n 必會等於 1
    // 會將所有 x 累乘的值乘給 sum，sum 就是 pow(x, n) 的答案
    double helper(double x, long long n, double sum) {
        if (n == 0) {
            return sum;
        }
        if (n % 2 == 0) {
            return helper(x * x, n / 2, sum);
        }
        else {
            return helper(x * x, n / 2, sum * x);
        }
    }

    double myPow(double x, long long n) {
        // 如果 n 是負數，將 x 變成倒數然後 n 改正數
        // e.g. (2^-5) = (1/2)^5
        if (n > 0) {
            return helper(x, n, 1);
        }
        else {
            return helper(1 / x, -n, 1);
        }
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures202412161058801.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures202412161058801.png)

#### 複雜度分析

令 `n` 為次方數。

- 時間複雜度： $O(\log n)$

- 空間複雜度： $O(1)$

    如果編譯器支持尾遞迴優化，遞迴 stack 不會增加，空間複雜度為 $O(1)$ ，否則為 $O(\log n)$ 。

### 2. Bit Manipulation

將 `n` 轉成二進位，則 `x` 的 `n` 次方會轉變成 `x` 的二進位次方，例如 $x^{11}$ 可以轉成 $x^{2^0 + 2^1 + 2^3}$ ，也就是 $x^{2^0} \cdot x^{2^1} \cdot x^{2^3}$ ，而 $x^{2^0} = x$ ， $x^{2^1} = x^2$ ， $x^{2^3} = x^8$ ，以此方式來迭代 `n` ，如果當前最後一個 $bit = 1$ ，則 $res = res \cdot x$ ，最後回傳 `res` 即可，反之則跳過。

e.g.

1. $x = 2$ ， $n = 11$ ， $res = 1$

    - $x = 2$ ， $n = (11)_{10} = (1011)_2$ ，最後一個 bit 是 1， $res = res \cdot x = 2$ ， $x = x^2$ ， $(n >>= 1) = 5$

    - $x = 4$， $n = (5)_{10} = (101)_2$ ，最後一個 bit 是 $1$ ， $res = res \cdot x = 8$ ， $x = x^2$ ， $(n >>= 1) = 2$

    - $x = 16$， $n = (2)_{10} = (10)_2$ ，最後一個 bit 是 $0$ ，跳過， $x = x^2$ ， $(n >>= 1) = 1$

    - $x = 256$， $n = (1)_{10} = (1)_2$ ，最後一個 bit 是 $1$ ， $res = res \cdot x = 2048$ ， $x = x^2$ ， $(n >>= 1) = 0$

    - $n = 0$ ，return $res = 2048$

#### 程式碼

```c++ {.line-numbers}
class Solution {
  public:
    double myPow(double x, long long n) {
        // 若 n < 0，將 x = 1/x，n 轉正
        if (n < 0) {
            x = 1 / x;
            n = -n;
        }

        // 遞迴計算次方
        double res = 1;
        while (n > 0) {
            // 判斷 n 最後一個 bit 是 1 還是 0
            if (n & 1) {
                res *= x;
            }
            n >>= 1; // n 往右移一個 bit
            x *= x;
        }

        return res;
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures202412161119906.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures202412161119906.png)

#### 複雜度分析

令 `n` 為次方數。

- 時間複雜度： $O(\log n)$

- 空間複雜度： $O(1)$
