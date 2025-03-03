# <center> [2683. Neighboring Bitwise XOR](https://leetcode.com/problems/neighboring-bitwise-xor/description/) </center>

## 題目敘述

[![](https://i.imgur.com/jbSveHG.png)](https://i.imgur.com/jbSveHG.png)

給一個長度為 `n` 整數陣列 `derived`，請確認是否存在一個整數陣列 `arr` 使得 $derived[i] = arr[i] \oplus arr[i + 1]$ ， $0 \leq i < n - 1$ ，如果 $i = n - 1$ ，則 $derived[i] = arr[i] \oplus arr[0]$ ，若存在這樣的 `arr` 則回傳 `true`，否則回傳 `false`。

## 解題思路

### 1. Bit Manipulation

觀察 $derived = [arr[0] \oplus arr[1], arr[1] \oplus arr[2], ..., arr[n - 2] \oplus arr[n - 1], arr[n - 1] \oplus arr[0]]$

如果將 `derived` 所有的 element 都做 XOR 運算，則結果為：

$arr[0] \oplus arr[1] \oplus arr[1] \oplus arr[2] \oplus ... \oplus arr[n - 2] \oplus arr[n - 1] \oplus arr[n - 1] \oplus arr[0] = 0$

因此這道題目可以透過將 `derived` 所有 element 做 XOR 運算，如果結果為 0，表示存在一個符合題意的 `arr` 陣列，回傳 `true`，反之則回傳 `false`。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    bool doesValidArrayExist(std::vector<int> &derived) {
        bool res = 0;
        for (const int &n : derived) {
            res ^= n;
        }

        return !res;
    }
};
```

[![](https://i.imgur.com/SjVvBe3.png)](https://i.imgur.com/SjVvBe3.png)

#### 複雜度分析

令 $n$ 為 `derived` 的長度。

- 時間複雜度： $O(n)$

- 空間複雜度： $O(1)$
