# <center> [LeetCode - 2558. Take Gifts From the Richest Pile](https://leetcode.com/problems/take-gifts-from-the-richest-pile/description/) </center>

## 題目敘述

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures202412121331831.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures202412121331831.png)

給一個正整數 array `gifts`，代表有 `n` 個禮物，每個禮物都有一個值，代表這個禮物的價值，以及一個正整數 `k`，代表可以執行 `k` 次操作，每次操作可以選擇將一個**價值最大**的禮物將值變成它的平方根，求執行完 `k` 次操作後，剩餘所有禮物的總和。

- 如果最大的值有兩個以上，則可以任選其中一個。

- 平方根的值會無條件捨去。

## 解題思路

### 1. Priority Queue

用一個 max heap 的 `priority queue` 來儲存所有禮物的值，每次操作時，將最大值取出，並將其平方根的值放回 `priority queue` 中，最後將所有禮物的值加總即為答案。

#### 程式碼

```c++ {.line-numbers}
class Solution {
  public:
    long long pickGifts(std::vector<int> &gifts, int k) {
        long long res = 0;
        std::priority_queue<int> pq;
        for (auto &gift : gifts) {
            res += gift; // 計算 gifts 總額
            pq.push(gift);
        }

        while (k--) {
            int top = pq.top();
            pq.pop();
            res -= (top - std::sqrt(top)); // 減去被拿走的 gift
            pq.push(std::sqrt(top));
        }

        return res;
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures202412121336442.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures202412121336442.png)

#### 複雜度分析

令 $n$ 為 `gifts` 的長度， $k$ 為操作次數。

- 時間複雜度： $O((n+k) \log n)$

- 空間複雜度： $O(n)$

### 2. Inplace Heapify（原地堆化）

相較於方法 1 額外創一個 `priority queue`，可以直接將 `gifts` 變成一個 max heap，這樣不用額外的空間，空間複雜度變成 $O(1)$ ，每次操作時，將最大值取出，並將其平方根的值放回 `gifts` 中，最後將所有禮物的值加總即為答案。

#### 程式碼

```c++ {.line-numbers}
class Solution {
  public:
    long long pickGifts(std::vector<int> &gifts, int k) {
        std::make_heap(gifts.begin(), gifts.end()); // 原地建立 max heap

        while (k-- && gifts[0] > 1) {
            std::pop_heap(gifts.begin(), gifts.end());  // 將 top 移到 尾端
            gifts.back() = sqrt(gifts.back());          // 將原本的 top 開根號
            std::push_heap(gifts.begin(), gifts.end()); // 將開根號後的 top 重新放入 heap
        }

        // 回傳剩餘 gifts 總額
        return accumulate(gifts.begin(), gifts.end(), 0LL);
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures202412121400640.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures202412121400640.png)

#### 複雜度分析

令 $n$ 為 `gifts` 的長度， $k$ 為操作次數。

- 時間複雜度： $O(n + k \log n)$

- 空間複雜度： $O(1)$
