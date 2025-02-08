# <center> [2657. Find the Prefix Common Array of Two Arrays](https://leetcode.com/problems/find-the-prefix-common-array-of-two-arrays/description/) </center>

## 題目敘述

[![](https://i.imgur.com/bptTC0Y.png)](https://i.imgur.com/bptTC0Y.png)

給兩個由 `[1, n]` 範圍所組成的整數陣列 `A` 和 `B`，請回傳一個陣列 `C`，其中 `C[i]` 代表 `A` 和 `B` 在 index `i` 之前（含）的共同 element 數量。

- `A` 和 `B` 長度相同。

- `A` 和 `B` 只包含 `[1, n]` 範圍內的整數，並且這些 element 都不重複。

## 解題思路

### 1. Hash Map

同時遍歷 `A` 和 `B`，並用一個 Hash Map 來記錄某個整數是否出現過，有兩種情況：

- 如果當前的整數 `k` 是第一次出現，那麼將 Hash Map 中 `k` 的值設為 `true`，表示 `k` 已經出現過了。

- 如果當前的整數 `k` 已經出現過了，那麼表示在先前的遍歷中 `k` 已經在 `A` 或 `B` 其中一個出現過，而這次是第二次出現，因此 `C[i]` 的值要加 1。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    std::vector<int> findThePrefixCommonArray(std::vector<int> &A, std::vector<int> &B) {
        int n = A.size();
        bool is_exist[n + 1];
        std::memset(is_exist, false, sizeof(is_exist));

        int cnt = 0;
        std::vector<int> res(n);
        for (int i = 0; i < n; ++i) {
            (!is_exist[A[i]]) ? is_exist[A[i]] = true : ++cnt;
            (!is_exist[B[i]]) ? is_exist[B[i]] = true : ++cnt;
            res[i] = cnt;
        }

        return res;
    }
};
```

[![](https://i.imgur.com/Jb6KDyO.png)](https://i.imgur.com/Jb6KDyO.png)

#### 複雜度分析

令 $n$ 為 `A` 和 `B` 的長度。

- 時間複雜度： $O(n)$

- 空間複雜度： $O(n)$
