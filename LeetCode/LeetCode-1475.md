# <center> [LeetCode - 1475. Final Prices With a Special Discount in a Shop](https://leetcode.com/problems/final-prices-with-a-special-discount-in-a-shop/description/) </center>

## 題目敘述

[![](https://i.imgur.com/shYGt68.png)](https://i.imgur.com/shYGt68.png)

給一個整數陣列 `prices`，代表每個商品的價格，對於每個商品都可以享有一個折扣，如果存在一個商品 `prices[j]` 滿足 $prices[j] \leq prices[i]$ 且 $j > i$，則可以享有 $prices[j]$ 的折扣，如果有多個 `j` 滿足則取最小的 `j`，若沒有符合條件的商品，則不享有折扣。回傳每個商品最終的價格。

e.g.

$prices = [8, 4, 6, 2, 3]$

- $i = 0$ ， $prices[0] = 8$ ，存在 $j = 1$ 滿足 $prices[j] \leq prices[i]$ 且 $j > i$ ，因此享有 $prices[1] = 4$ 的折扣，最終價格為 $8 - 4 = 4$ 。

- $i = 1$ ， $prices[1] = 4$ ，存在 $j = 3$ 滿足 $prices[j] \leq prices[i]$ 且 $j > i$ ，因此享有 $prices[3] = 2$ 的折扣，最終價格為 $4 - 2 = 2$ 。

- $i = 2$ ， $prices[2] = 6$ ，存在 $j = 3$ 滿足 $prices[j] \leq prices[i]$ 且 $j > i$ ，因此享有 $prices[3] = 2$ 的折扣，最終價格為 $6 - 2 = 4$ 。

- $i = 3$ ， $prices[3] = 2$ ，不存在 $j$ 滿足 $prices[j] \leq prices[i]$ 且 $j > i$ ，因此不享有折扣，最終價格為 $2$ 。

- $i = 4$ ， $prices[4] = 3$ ，不存在 $j$ 滿足 $prices[j] \leq prices[i]$ 且 $j > i$ ，因此不享有折扣，最終價格為 $3$ 。

- 最終價格為 `[4, 2, 4, 2, 3]`

## 解題思路

### 1. Monotonic Stack

找右區間第一個 $\leq$ 自身的值可以使用單調遞增的 stack 來解決，從右往左遍歷，如果當前 element `cur` 比 stack 頂部的 element `top` 還要小，則將 `top` pop，直到 stack 為空或 $top \leq cur$ ，此時 `top` 就是第一個右區間中 $\leq cur$ 的值，將 `cur` push in stack 並減去 `top`，遍歷完整個 array 後即可得到最終價格。

e.g.

$prices = [8, 4, 6, 2, 3]$

- 初始化 stack 為空。

- $i = 4$ ， $cur = 3$ ，`stack` 為空，將 3 push in `stack`， $stack = [3]$ 。

- $i = 3$ ， $cur = 2$ ，`stack` 頂部為 3 ， $3 > 2$ ，將 3 pop，`stack` 為空，將 2 push in `stack`， $stack = [2]$ 。

- $i = 2$ ， $cur = 6$ ，`stack` 頂部為 2 ， $2 < 6$ ，將 6 push in `stack`， $stack = [2, 6]$ ， $prices[2] = 6 - 2 = 4$ 。

- $i = 1$ ， $cur = 4$ ，`stack` 頂部為 6 ， $6 > 4$ ，將 6 pop，`stack` 頂部為 2 ， $2 < 4$ ，將 4 push in `stack`， $stack = [2, 4]$ ， $prices[1] = 4 - 2 = 2$ 。

- $i = 0$ ， $cur = 8$ ，`stack` 頂部為 4 ， $4 < 8$ ，將 8 push in `stack`， $stack = [2, 4, 8]$ ， $prices[0] = 8 - 4 = 4$ 。

- 遍歷完畢，最終價格為 `[4, 2, 4, 2, 3]`。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    std::vector<int> finalPrices(std::vector<int> &prices) {
        std::stack<int> st;

        // 找右區間第一個小於等於自身的值，從右往左遍歷
        for (int i = prices.size() - 1; i >= 0; --i) {
            while (!st.empty() && st.top() > prices[i]) {
                st.pop();
            }

            int tmp = prices[i]; // 由於 prices[i] 可能會被修改，所以需要暫存
            if (!st.empty()) {
                prices[i] -= st.top();
            }
            st.emplace(tmp);
        }

        return prices;
    }
};
```

[![](https://i.imgur.com/F8H0hHU.png)](https://i.imgur.com/F8H0hHU.png)

#### 複雜度分析

令 $n$ 為 `prices` 的長度。

- 時間複雜度： $O(n)$

- 空間複雜度： $O(n)$
