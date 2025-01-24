# <center> [2466. Count Ways To Build Good Strings](https://leetcode.com/problems/count-ways-to-build-good-strings/description/) </center>

## 題目敘述

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures202412301526775.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures202412301526775.png)

給四個整數 `low`, `high`, `zero`, `one`，請通過以下操作來構建長度在 `low` 和 `high` 之間（包含兩端）的字串：  

- 初始字串為空

- 每次操作可以選擇在字串後面添加 `zero` 個 `0` 或 `one` 個 `1`

- 操作次數不限制

請問有多少種不同的字串長度為 `low` 到 `high` 之間（包含兩端），答案可能很大請 mod $10^9+7$ 後返回。

## 解題思路

### 1. Dynamic Programming

這是一種和爬樓梯非常像的問題，可以使用動態規劃來解決。

令當前建構的字串長度為 `k`、合法的字串數量為 `res`，如果 $low \leq k \leq high$，則表示當前分支是合法的字串， $res + 1$ ，反之則不合法，繼續往下走找到合法的字串。先用 DFS 來實現，如下程式碼所示：

```cpp
class Solution {
  private:
    const int N = 1000000007;
    int low, high, zero, one;

  public:
    int dfs(int k) {
        // k 超過 high 則表示當前分支不合法
        if (k > high) {
            return 0;
        }

        // 可以用 k >= low 來判斷當前分支是否合法
        // 如果 k 在 low 和 high 之間，則表示當前分支是合法的字串
        return (dfs(k + zero) + dfs(k + one) + (k >= low)) % N;
    }
    int countGoodStrings(int low, int high, int zero, int one) {
        this->low = low, this->high = high, this->zero = zero, this->one = one;
        return dfs(0);
    }
};
```

可得到遞迴公式：

$$
f(k) =
\begin{cases}
0 & k > \text{high}, \\
\big( f(k + \text{zero}) + f(k + \text{one}) + \mathbb{I}(k \geq \text{low}) \big) \mod N & k \leq \text{high}.
\end{cases}
$$

$$
\mathbb{I}(k \geq \text{low}) =
\begin{cases}
1, & k \geq \text{low}, \\
0, & k < \text{low}.
\end{cases}
$$

轉為狀態轉移公式：

$$
dp[k] =
\begin{cases}
0 & k > \text{high}, \\
\big( dp[k + \text{zero}] + dp[k + \text{one}] + \mathbb{I}(k \geq \text{low}) \big) \mod N & k \leq \text{high}.
\end{cases}
$$

$$
\mathbb{I}(k \geq \text{low}) =
\begin{cases}
1, & k \geq \text{low}, \\
0, & k < \text{low}.
\end{cases}
$$

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    int countGoodStrings(int low, int high, int zero, int one) {
        const int N = 1000000007;
        int dp[high + 1];
        std::memset(dp, 0, sizeof(dp));

        for (int i = high; i >= 0; --i) {
            dp[i] += (i >= low);
            // 處理邊界條件
            if (i + zero <= high) {
                dp[i] += dp[i + zero];
            }
            if (i + one <= high) {
                dp[i] += dp[i + one];
            }
            dp[i] %= N;
        }

        return dp[0];
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures202412301621680.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures202412301621680.png)

#### 複雜度分析

- 時間複雜度： $O(high)$

- 空間複雜度： $O(high)$

---

對於這樣的演算法可以進一步做優化，假設 `zero` 和 `one` 的 GCD 為 `g`，那麼 $[low, high]$ 之間的數字就會是 $a \cdot g$ 和 $b \cdot g$ ，其中 $a$ 和 $b$ 是任意整數，因此可以將查找的範圍壓縮，如下所示：

$$
\begin{cases}
zero &= zero \div g \\
one &= one \div g \\
low &= \lceil low \div g \rceil \\
high &= \lfloor high \div g \rfloor \\
\end{cases}
$$

需要注意的是 `low` 是向上取整，`high` 是向下取整，向上取整分為可以被整除或是不可以被整除兩種情況，假設有一整數 `n` 和除數 `g`，將 `n` 加上 `g-1` 再除以 `g`，這樣就可以保證 `n` 是向上取整的，這是利用 `c++` 除法預設為向下整除的特性，需要注意的是這種方式只適合 $n > 0$ 的情況。

- `n` 可以被整除

$$
\frac{n + (g-1)}{g}  = \frac{n}{g} + \frac{g-1}{g} = \frac{n}{g}
$$

- `n` 不能被整除

$$\frac{n + (g-1)}{g}  = \frac{n - (n \bmod g)}{g} + \frac{g-1 + (n \bmod g)}{g} = \frac{n}{g} + 1
$$

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    int countGoodStrings(int low, int high, int zero, int one) {
        const int N = 1000000007;
        // 優化查找範圍，以 GCD 來壓縮範圍
        int g = std::gcd(zero, one);
        low += g - 1; // 為了處理向上取整
        zero /= g, one /= g, low /= g, high /= g;

        int dp[high + 1];
        std::memset(dp, 0, sizeof(dp));

        for (int i = high; i >= 0; --i) {
            // 要記得處理邊界條件
            dp[i] += (i >= low);
            dp[i] += (i + zero <= high) ? dp[i + zero] : 0;
            dp[i] += (i + one <= high) ? dp[i + one] : 0;
            dp[i] %= N;
        }

        return dp[0];
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures202412301709644.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures202412301709644.png)

#### 複雜度分析

令 $g$ 為 `zero` 和 `one` 的最大公因數。

- 時間複雜度： $O(\frac{high}{g})$

- 空間複雜度： $O(\frac{high}{g})$
