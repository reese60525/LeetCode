# <center> [2425. Bitwise XOR of All Pairings](https://leetcode.com/problems/bitwise-xor-of-all-pairings/description/) </center>

## 題目敘述

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501161423491.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501161423491.png)

給兩個整數陣列 `nums1` 和 `nums2`，將所有 `nums1[i]` 和 `nums2[j]` 的 element 兩兩一組來配對，並且將所有配對的結果做 XOR 運算，回傳最後的 XOR 結果。

## 解題思路

### 1. Bit Manipulation

令 `nums1` = $[x_1, x_2, ..., x_n]$ ，`nums2` = $[y_1, y_2, ..., y_m]$

則所有配對的結果為：

$$
[x_1 \oplus y_1, x_1 \oplus y_2, ..., x_1 \oplus ym, x_2 \oplus y_1, x_2 \oplus y_2, ..., x_2 \oplus y_m, ..., x_n \oplus y_1, x_n \oplus y_2, ..., x_n \oplus y_m]
$$

將這些配對結果做 XOR 運算，根據 XOR 的交換率，最後的 XOR 結果為：

$$
[x_1 \oplus x_1 \oplus  ... \oplus x_1] \oplus [x_2 \oplus x_2 \oplus  ... \oplus x_2] \oplus ... \oplus [x_n \oplus x_n \oplus  ... \oplus x_n] \oplus [y_1 \oplus y_1 \oplus  ... \oplus y_1] \oplus [y_2 \oplus y_2 \oplus  ... \oplus y_2] \oplus ... \oplus [y_m \oplus y_m \oplus  ... \oplus y_m]
$$

其中 $x_i$ 的 XOR 次數為 $m$ 次， $y_j$ 的 XOR 次數為 $n$ 次，而自身和自身做若干次 XOR 運算會有兩種情況：

1. 若整數 `k` 和自身做**奇數次**的 XOR 運算，則結果為 `k`。
2. 若整數 `k` 和自身做**偶數次**的 XOR 運算，則結果為 `0`。

因此分別判斷 `nums1` 和 `nums2` 的長度，對於 `nums1` 來說如果 `nums2` 的長度 `m` 是奇數，則需要將 `nums1` 所有 element 做 XOR 運算。同理，對於 `nums2` 來說如果 `nums1` 的長度 `n` 是奇數，則需要將 `nums2` 所有 element 做 XOR 運算，最後再將兩者的計算結果做 XOR 運算即可得到答案。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    int xorAllNums(std::vector<int> &nums1, std::vector<int> &nums2) {
        int res = 0;

        if (nums2.size() & 1) {
            for (const int &n : nums1) {
                res ^= n;
            }
        }

        if (nums1.size() & 1) {
            for (const int &n : nums2) {
                res ^= n;
            }
        }

        return res;
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501161450459.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501161450459.png)

時間複雜度： $O(n + m)$ ，其中 $n$ 和 $m$ 分別為 `nums1` 和 `nums2` 的長度。

空間複雜度： $O(1)$ 。
