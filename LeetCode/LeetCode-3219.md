# <center> [3219. Minimum Cost for Cutting Cake II](https://leetcode.com/problems/minimum-cost-for-cutting-cake-ii/description/) </center>

## 題目敘述

[![](https://i.imgur.com/fgBIb5q.png)](https://i.imgur.com/fgBIb5q.png)

**這題是 [3218. Minimum Cost for Cutting Cake I](https://leetcode.com/problems/minimum-cost-for-cutting-cake-i/description/) 的測資加強版，解法一模一樣**

給一個 $m \times n$ 矩陣，代表一個蛋糕，可以將蛋糕切小塊，最小能切為 $1 \times 1$ 的蛋糕，row and column 分別能切 $m - 1$ 和 $n - 1$ 次。給兩個一維整數陣列 `horizontalCuts` 和 `verticalCuts`，size 分別為 $m - 1$ 和 $n - 1$ ，分別代表將蛋糕在水平和垂直方向上切割所需要的成本。

請找出將蛋糕全部切成 $1 \times 1$ 的蛋糕所需要的最小成本。

**蛋糕切塊後就算變小塊，但該蛋糕切割所需要的成本仍然是原本的成本，不會因為切塊後而改變。**

- 比如說有一個 $2 \times 5$ 的蛋糕，垂直方向的成本為 `[1, 2, 3, 4]`，如果在第二個垂直切割點（成本為 3）將其切成 $2 \times 2$ 和 $2 \times 3$ 的蛋糕，則對於 $2 \times 2$ 的蛋糕，其垂直方向切割成本為 `[1]`，而 $2 \times 3$ 的蛋糕，其成本為 `[3, 4]`。

## 解題思路

### 1. Greedy and Priority Queue

一個簡單直接的想法，反正最後每個切割點都必須要切，那就先將成本最大的先切。假設有一個 $m \times n$ 的蛋糕，如果已經切到變成 $m$ 個 $1 \times 2$ 和 $m \times (n - 2)$ 個 $1 \times 1$ 的蛋糕，現在只剩下一個垂直切割能切，令其成本為 `k`，此時切下去的總成本為 $cost = k x m$ ，我們要想辦法讓這個 `cost` 最小，所以這個 `k` 要越小越好，也就是說成本越小的切割點要留到最後再切。

驗證：假設有一個矩陣為 $m \times n$ ，`horizontalCuts` 和 `verticalCuts` 分別為 `[c1, c1, ..., c1]` 和 `[c2, c2, ..., c2]`，分別計算以下兩種切割方式：

1. 先全部切水平方向，再切垂直方向，總成本為：

    $$
    cost1 = c1 \cdot (m-1) + (c2 \cdot m) \cdot (n-1) = c2 \cdot m \cdot n + (c1 - c2) \cdot m - c1
    $$

2. 先全部切垂直方向，再切水平方向，總成本為：

    $$
    cost2 = c2 \cdot (n-1) + (c1 \cdot n) \cdot (m-1) = c1 \cdot m \cdot n + (c2 - c1) \cdot n - c2
    $$

令 `c1` = 1001、`c2` = 1000，`m` 和 `n` 的範圍為 `[1, 10^5]`，用以下程式碼驗證是否有 $cost1 > cost2$ 的情況。

```cpp {.line-numbers}
#include <cstdint>
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Data {
  public:
    uint64_t c1, c2, m, n;
    void setVal(uint64_t c1, uint64_t c2, uint64_t m, uint64_t n) {
        this->c1 = c1;
        this->c2 = c2;
        this->m = m;
        this->n = n;
    }
};

int main() {
    Data d;
    uint64_t cnt = 0;
    for (int i = 1; i <= 1e5; ++i) {
        for (int j = 1; j <= 1e5; ++j) {
            d.setVal(1001, 1000, i, j);
            uint64_t cost1 = d.c2 * d.m * d.n + (d.c1 - d.c2) * d.m - d.c1; // 水平切割
            uint64_t cost2 = d.c1 * d.m * d.n + (d.c2 - d.c1) * d.n - d.c2; // 垂直切割
            // 當 cost1 > cost2 時，代表先切垂直方向的總成本會比較小，與假設矛盾
            if (cost1 > cost2) {
                std::cout << "cost1 > cost2 in (m, n) = (" << i << ", " << j << ")\n";
                exit(0);
            }

            ++cnt;
        }
    }
    std::cout << "沒有發生 cost1 > cost2 的事件，驗證假設正確，總執行次數: " << cnt << '\n';

    return 0;
}
```

會得到以下結果：

```output
沒有發生 cost1 > cost2 的事件，總執行次數: 10000000000
```

因此可以證明先切成本較大的切割點，總成本會比較小。

#### 程式碼

```cpp {.line-numbers}
// Priority Queue
class Solution {
  public:
    long long minimumCost(int m, int n, std::vector<int> &horizontalCut, std::vector<int> &verticalCut) {
        std::priority_queue<std::pair<int, bool>> pq; // 儲存所有切割成本，queue top 為最大的成本

        // 將垂直和水平分割的成本放入 pq 中
        // is_row 用來判斷該分割成本是水平還是垂直的分割成本
        auto buildPQ = [&](std::vector<int> arr, bool is_row) -> void {
            for (size_t i = 0; i < arr.size(); ++i) {
                pq.push({arr[i], is_row});
            }
        };
        buildPQ(horizontalCut, true);
        buildPQ(verticalCut, false);

        // 計算總成本，h_cnt 和 v_cnt 分別計算蛋糕目前在水平方向和垂直方向共被切成幾塊
        long long res = 0, h_cnt = 1, v_cnt = 1;
        while (!pq.empty()) {
            auto [cost, is_row] = pq.top();
            pq.pop();

            // 成本計算方式為： 該次切割成本 * 該方向上有幾個蛋糕
            // 例如要切水平方向的蛋糕，則這次切割的總成本 = 切割成本 * 目前垂直方向上有幾個蛋糕
            res += is_row ? cost * v_cnt : cost * h_cnt;
            // 更新目前水平和垂直方向上有幾個蛋糕
            h_cnt += is_row;
            v_cnt += !is_row;
        }

        return res;
    }
};
```

[![](https://i.imgur.com/j0dQAtV.png)](https://i.imgur.com/j0dQAtV.png)

#### 複雜度分析

令 $h$ 和 $v$ 分別為 `horizontalCuts` 和 `verticalCuts` 的長度。

- 時間複雜度： $O((h + v) \cdot \log (h + v))$

- 空間複雜度： $O(h + v)$

### 2. Greedy and Sorting and Two Pointer

和方法一一樣的概念，將 `horizontalCuts` 和 `verticalCuts` 排序，用 two pointer 迭代 `horizontalCuts` 和 `verticalCuts`，將成本較大的先切割，直到 `horizontalCuts` 和 `verticalCuts` 都迭代完為止。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    long long minimumCost(int m, int n, std::vector<int> &horizontalCut, std::vector<int> &verticalCut) {
        // 要由大排到小
        std::sort(horizontalCut.begin(), horizontalCut.end(), std::greater<int>());
        std::sort(verticalCut.begin(), verticalCut.end(), std::greater<int>());

        // h_cnt 和 v_cnt 分別代表目前水平和垂直方向上有幾個蛋糕
        int i = 0, j = 0, h_cnt = 1, v_cnt = 1;
        long long res = 0;
        while (i < m - 1 || j < n - 1) {
            // 邊界判斷避免 index out of range
            int h_cost = i < m - 1 ? horizontalCut[i] : 0;
            int v_cost = j < n - 1 ? verticalCut[j] : 0;
            // 判斷目前哪個成本比較大，並將該成本計入總成本中
            bool is_h_bigger = h_cost > v_cost;
            res += is_h_bigger ? h_cost * v_cnt : v_cost * h_cnt;
            // 更新 index 和 目前水平和垂直方向上有幾個蛋糕
            is_h_bigger ? ++i : ++j;
            is_h_bigger ? ++h_cnt : ++v_cnt;
        }

        return res;
    }
};
```

[![](https://i.imgur.com/V3fZcGf.png)](https://i.imgur.com/V3fZcGf.png)

#### 複雜度分析

令 $h$ 和 $v$ 分別為 `horizontalCuts` 和 `verticalCuts` 的長度。

- 時間複雜度： $O(h \cdot \log h + v \cdot \log v)$

- 空間複雜度： $O(\log h + \log v)$

    $O(\log h)$ 和 $O(\log v)$ 各為 `horizontalCuts` 和 `verticalCuts` 排序所需的空間。

### 3. Greedy and Counting Sort

對於上述演算法可以進一步做優化，可以發現如果水平切割或垂直切割有 `k` 個大小相同的 `cost` 就得重複計算 `k` 次，以水平切割為例子，當前切割的總成本為：

$$
\text{水平切割的成本} \times \text{垂直方向的蛋糕數量} = \text{h\_cost} \times \text{v\_cnt}
$$

並且切割後會是 **水平方向** 的蛋糕增加 1 個，垂直方向的蛋糕數量並沒有變，所以若是下一個 `h_cost` 跟上一次一樣，那麼當前切割的總成本也會跟上一次一樣。

要如何優化重複計算的部分呢？可以用兩個整數陣列 `h_freq` 和 `v_freq` 儲存水平和垂直切割的每種 `cost` 出現頻率，並且記錄 `max_cost`，假設水平切割有個 $h_cost = 50$ 出現了 12 次，則 $h_freq[50] = 12$ 。然後從 `max_cost` 開始同時遍歷這兩個整數陣列，當前切割總成本會變成： $cost \times cnt \times freq[i]$ ，這樣就能將原本重複 `k` 次的計算變成只要算一次就好，缺點是會需要額外的空間。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    long long minimumCost(int m, int n, std::vector<int> &horizontalCut, std::vector<int> &verticalCut) {
        // 紀錄每個切割成本的出現頻率和最大成本
        int max_val = 0;
        std::vector<int> h_freq(1001, 0), v_freq(1001, 0);
        for (int &n : horizontalCut) {
            ++h_freq[n];
            max_val = std::max(max_val, n);
        }
        for (int &n : verticalCut) {
            ++v_freq[n];
            max_val = std::max(max_val, n);
        }

        // h_cnt 和 v_cnt 分別計算蛋糕目前在水平方向和垂直方向共被切成幾塊

        long long res = 0, h_cnt = 1, v_cnt = 1;
        for (size_t cost = max_val; cost != SIZE_MAX; --cost) {
            res += cost * v_cnt * h_freq[cost];
            h_cnt += h_freq[cost];
            res += cost * h_cnt * v_freq[cost];
            v_cnt += v_freq[cost];
        }

        return res;
    }
};
```

[![](https://i.imgur.com/PAdNDr0.png)](https://i.imgur.com/PAdNDr0.png)

#### 複雜度分析

令 $h$ 和 $v$ 分別為 `horizontalCuts` 和 `verticalCuts` 的長度。

- 時間複雜度： $O(h + v)$

- 空間複雜度： $O(1)$

    雖然是 $O(1)$ 但實際上會使用 $O(1001 \cdot 2) = O (2002)$ 的空間，而 `m` 和 `n` 最多為 $10^5$ ，原本的 $O(\log h + \log v)$ 最多只有 $O(316 + 316) = O(632)$ ，因此記憶體使用量是增加的。
