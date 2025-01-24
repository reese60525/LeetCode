# <center> [1014. Best Sightseeing Pair](https://leetcode.com/problems/best-sightseeing-pair/description/) </center>

## 題目敘述

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241227105051282.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241227105051282.png)

給一個整數陣列 `values`，其中 `values[i]` 代表第 `i` 個景點的評分，而兩個景點 `i` 和 `j` 的**觀光價值**為兩景點的評分減去距離也就是 $values[i] + values[j] - (j - i)$ ，`i` 必須小於 `j`，請找出最大的觀光價值。

## 解題思路

### 1. Greedy

我們可以將觀光價值的式子看成： $(values[i] + i) + (values[j] - j)$ 。

對於任意一個景點 `j` 來說，要找出其最大觀光價值，因為 $(values[j] - j)$ 是固定值，所以要找 $(values[i] + i)$ 最大的 `i`，因此我們可以用 $j = 1$ 從左到右遍歷 `values`，並且維護一個變數 `maxLeft` 來儲存當前 `j` 左側最大的 $(values[i] + i)$ ，而最大觀光價值為 $res = max(res, maxLeft + values[j] - j)$ 。

如果 `j` 右側有一個 `k` 其 $(values[k] + k) > (values[i] + i)$ 呢？當遍歷到 `k` 時 `k` 也是會選擇其左側最大的 $values[i] + [i]$ ，而當前的 `j` 也會在考慮的範圍，所以不用擔心沒有考慮到 `j` 右側的值。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    int maxScoreSightseeingPair(std::vector<int> &values) {
        // max_left[i] 為 k = [0,i-1] 之間的 max(values[k] - k)
        int max_left = values[0] + 0, res = 0;

        for (int i = 1; i < values.size(); ++i) {
            res = std::max(res, (values[i] - i) + max_left);
            max_left = std::max(max_left, values[i] + i);
        }

        return res;
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241227111548328.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241227111548328.png)

#### 複雜度分析

令 $n$ 為 `values` 的長度。

- 時間複雜度： $O(n)$

- 空間複雜度： $O(1)$
