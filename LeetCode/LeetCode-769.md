# <center> [769. Max Chunks To Make Sorted](https://leetcode.com/problems/max-chunks-to-make-sorted/description/) </center>

## 題目敘述

[![](https://i.imgur.com/qROfqdp.png)](https://i.imgur.com/qROfqdp.png)

給一個由 `[0, n-1]` 不重複的整數組成的array `arr`，將其進行以下操作：

1. 將 `arr` 分割成一個或多個 subarray

2. 對每個 subarray 進行排序

3. 將每個 subarray 合併成一個 sorted array

4. 合併後的 sorted array 必須是 `0, 1, ..., n-1` 的升序排序

請找出經過以上操作後，subarray 所能達到的最大數量。

e.g.

1. $arr1 = [4, 3, 2, 1, 0]$

    - 只能將其分割成 `[[4, 3, 2, 1, 0]]`，排序後變成 `[[0, 1, 2, 3, 4]]`，合併後為 `[0, 1, 2, 3, 4]`，因此最大的 subarray 數量為 1。

2. $arr1 = [1, 0, 2, 3, 4]$

   - 可以將其分割成 `[[1, 0], [2], [3], [4]]`，排序後變成 `[[0, 1], [2], [3], [4]]`，合併後為 `[0, 1, 2, 3, 4]`，subarray 數量為 4。

   - 可以將其分割成 `[[1, 0, 2, 3, 4]]`，排序後變成 `[[0, 1, 2, 3, 4]]`，合併後為 `[0, 1, 2, 3, 4]`，subarray 數量為 1。

   - 可以將其分割成 `[[1, 0, 2], [3], [4]]`，排序後變成 `[[0, 1, 2], [3], [4]]`，合併後為 `[0, 1, 2, 3, 4]`，subarray 數量為 3。

   - 以此類推...可以得到 subarray 最大數量為 4。

## 解題思路

### Greedy

由於 `arr` 中的元素都是 `[0, n-1]` 的**非重複**整數，因此其排序後的 value 正好會等於 index。而**非重複**的特性也代表在區間 `[i, j]` 之間的 element 最大 value 必為 `j`。

利用以上兩點特性，遍歷 `arr` 並記錄 `arr` 當前的 `maxValue`，如果 $i = maxValue$ 時，表示 `maxValue` 已經能放到正確的位置，由於 `arr` 中沒有重複的 element 並且當前區間的 value 都小於 `maxValue`，因此當前區間的所有 element 都能放到正確的位置，可以將該區間進行切割，subarray 數量加 1。

如果 $i < maxValue$ ，表示當前區間無法將 `maxValue` 放到正確的位置，需要將區間擴大，繼續遍歷 `arr` 找能將 `maxValue` 放到正確位置的區間。

e.g.

$arr = [1, 0, 2, 3, 4]$ ， $max\_val = 0$

- 更新 `max_val` 為 1， $max\_val > i = 0$ ，`max_val` 應當放到 $index = 1$ 的位置，當前區間 `[0, 0]` 無法滿足，繼續遍歷 `arr`。

- 由 $max\_val = i$ 可得知當前位置是放置 `max_val` 的正確位置，將 subarray 數量加 1。

- 更新 `max_val` 為 2， $max\_val = i$ ，將 subarray 數量加 1。

- 更新 `max_val` 為 3， $max\_val = i$ ，將 subarray 數量加 1。

- 更新 `max_val` 為 4， $max\_val = i$ ，將 subarray 數量加 1。

- 遍歷結束，subarray 數量為 4。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    int maxChunksToSorted(std::vector<int> &arr) {
        int res = 0, n = arr.size(), max_val = 0;

        for (int i = 0; i < n; ++i) {
            max_val = std::max(max_val, arr[i]);
            res += (i == max_val);
        }

        return res;
    }
};
```

[![](https://i.imgur.com/Ggapjio.png)](https://i.imgur.com/Ggapjio.png)

#### 複雜度分析

令 $n$ 為 `arr` 的長度。

- 時間複雜度： $O(n)$

- 空間複雜度： $O(1)$
