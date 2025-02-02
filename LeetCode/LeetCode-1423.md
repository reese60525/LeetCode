# <center> [1423. Maximum Points You Can Obtain from Cards](https://leetcode.com/problems/maximum-points-you-can-obtain-from-cards/description/) </center>

## 題目敘述

[![](https://i.imgur.com/1o8Ni6x.png)](https://i.imgur.com/1o8Ni6x.png)

給一組整數陣列 `cardPoints` 和整數 `k`，分別代表每張卡片的點數和要取幾張，每次都可以選擇從 `cardPoints` 的頭或尾取一張卡片，直到取完 `k` 張卡片，請問可以得到的最大點數總和是多少？

## 解題思路

### 1. Sliding Window

考慮到這組輸入： $cardPoints = [1, 2, 3, 4, 5, 6, 1]$ ， $k = 4$ ，有以下幾種選擇方式：

1. 選擇 `[[1, 2, 3, 4], []]`

2. 選擇 `[[1, 2, 3], [1]]`

3. 選擇 `[[1, 2], [6, 1]]`

4. 選擇 `[[1], [5, 6, 1]]`

5. 選擇 `[[], [4, 5, 6, 1]]`

可以發現這就是一個頭尾相連的 Sliding Window，而用 Sliding Window 有兩種解法：

1. 直接計算選取的卡片的最大選取總和

2. 計算不選取的卡片的最小總和，最大選取總和 = 所有卡片總和 - 最小不選取總和

---

第一種解法，先計算出左邊前 `k` 張卡片總和，然後開始滑窗，每次滑動時，將左邊卡片移除一張，右邊卡片加一張，並更新最大總和。

#### 程式碼

``` cpp {.line-numbers}
// 計算選取的卡片
class Solution {
  public:
    int maxScore(std::vector<int> &cardPoints, int k) {
        int n = cardPoints.size();
        // 計算前 k 張卡片的總和
        int cur_val = std::accumulate(cardPoints.begin(), cardPoints.begin() + k, 0);
        int res = cur_val;

        // 每次迭代都將左右兩端的 window 往左移動一格
        for (int i = k - 1; i >= 0; --i) {
            cur_val -= cardPoints[i];
            cur_val += cardPoints[n - k + i];
            res = std::max(res, cur_val);
        }

        return res;
    }
};
```

[![](https://i.imgur.com/agNdqLB.png)](https://i.imgur.com/agNdqLB.png)

#### 複雜度分析

令 `k` 為要選取的卡片數量。

- 時間複雜度： $O(k)$

- 空間複雜度： $O(1)$

---

第二種解法，滑窗計算每個不選取的卡片總和，然後取最小值，最大選取總和 = 所有卡片總和 - 最小不選取總和。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    int maxScore(std::vector<int> &cardPoints, int k) {
        int n = cardPoints.size();
        int x = n - k; // 不選擇的卡片數量

        int total = 0, cur_sum = 0, min_sum = INT_MAX;
        for (int i = 0; i < n; ++i) {
            total += cardPoints[i];
            cur_sum += cardPoints[i];

            // 當不選擇的數量滿足 window 大小後才開始計算
            if (i + 1 >= x) {
                min_sum = std::min(min_sum, cur_sum);
                cur_sum -= cardPoints[i + 1 - x];
            }
        }

        // x = 0 是例外條件，代表全部選擇，直接回傳 total
        return x == 0 ? total : total - min_sum;
    }
};
```

[![](https://i.imgur.com/xjLj876.png)](https://i.imgur.com/xjLj876.png)

#### 複雜度分析

令 $n$ 為 `cardPoints` 的長度。

- 時間複雜度： $O(n)$

- 空間複雜度： $O(1)$
