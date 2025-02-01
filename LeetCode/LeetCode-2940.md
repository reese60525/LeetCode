# <center> [LeetCode - 2940. Find Building Where Alice and Bob Can Meet](https://leetcode.com/problems/find-building-where-alice-and-bob-can-meet/description/) </center>

## 題目敘述

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241222150446589.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241222150446589.png)

給一個 1D integer array `heights`，代表每棟建築物的高度，以及 2D integer array `queries`，代表 Alice 和 Bob（以下簡稱 `a` 和 `b`）的所在建築物的 index。

對於某個人在建築物 index = `i` 上，假使有一個建築物 index = `j` 滿足 $i < j$ 且 $heights[i] < heights[j]$ ，則該人可以從建築物 `i` 移動到建築物 `j`。

請找出每個 query 的 `a` 和 `b` 可以一起到達的最左邊建築物 index，若是沒有這樣的建築物則 return -1。

e.g.

`heights` = {6, 4, 8, 5, 2, 7, 8}, `queries` = {{0, 1}, {0, 3}, {2, 4}, {3, 4}, {2, 2}, {5, 6}}

- 對於 `queries[0]`，`a` 可以從 `heights[0]` = 6 移動到 `heights[2]` = 8，`b` 可以從 `heights[1]` = 4 移動到 `height[2]` = 8，`res[0]` = 2。

- 對於 `queries[1]`，`a` 可以從 `heights[0]` = 6 移動到 `heights[5]` = 7，`b` 可以從 `heights[3]` = 5 移動到 `height[5]` = 7，`res[1]` = 5。

- 對於 `queries[2]`，`a` 和 `b` 沒有可以一起到達的建築物，`res[2]` = -1。

- 對於 `queries[3]`，`a` 可以從 `heights[3]` = 5 移動到 `heights[5]` = 7，`b` 可以從 `heights[4]` = 2 移動到 `height[5]` = 7，`res[3]` = 5。

- 對於 `queries[4]`，`a` 和 `b` 原本就在同個建築物，`res[4]` = 2。

- 對於 `queries[5]`，`a` 可以從 `heights[5]` = 7 移動到 `heights[6]` = 8，`b` 不用移動，`res[6]` = 5。

## 解題思路

對於 `queries` 的處理分為兩種：

- 離線處理：按照自己定義的處理順序來回答 query。這種處理方式需要將所有的查詢提前收集，排序後根據某種規則一次性處理。

- 在線處理：按照 query 的輸入順序來回答 query。這種處理方式可以在輸入查詢時馬上回答。

### 1. Hash Map and Sorting and Monotonic Stack （離線處理）

首先對 `queries` 的 `a` 和 `b` 進行比較和交換，使得 $queries[i] = \{a, b\}, a \leq b$ ，對於 `queries[i]` 分成三種情況：

1. $a = b$ ，則 $res[i] = b$ 。

2. $heights[a] < heights[b]$ ，則 $res[i] = b$ 。

3. $heights[a] \geq heights[b]$ ，則 $res[i] = j$ ，`j` 為 `[a+1, n-1]` 範圍中 $heights[j] > heights[a]$ 的最小值。

前兩種情況可以簡單判斷來處理，第三種情況則需要使用 `monotonic stack` 來處理，用一個 1D array `highest` 來記錄每個建築物右邊第一個比它高的建築物 index，若沒有則設為 -1。令 `j` = `highest[b]`，從 `j` 開始往右搜尋，如果 `heights[j]` > `heights[a]`，則 `res[i]` = `j`，否則根據 `monotonic stack` 的特性，`j` 到 `highest[j]` 之間的建築物都不會比 `j` 高，因此可以將 `j` = `highest[j]` 來跳躍右邊的建築物往右搜尋。如果都找不到則 $res[i] = -1$ 。

此外還要用 `hash map` 儲存查詢過的結果，令 `mp[a]` 為最近一次查詢 `queries[i] = {a, b}` 的結果，透過將查詢過的資料記憶化來避免重複查找的動作。由於 `queries` 已經以 `b` 由小到大排序過，假設最近一次查找過 `queries[i] = {a, b}`，那麼之後查詢 `queries[i'] = {a, b'}` 時，一定是 $b' \geq b$ ，因此分成三種情況：

1. $mp[a] \geq b$ ，則 $res[i] = map[a]$ 。

2. $mp[a] = -1$ ，表示 `queries[i'] = {a, b}` 是無法到達共同建築物的，又由於 $b' \geq b$ ，`queries[i'] = {a, b'}` 也無法到達共同建築物， $res[i] = -1$ 。

3. $mp[a] < b'$ ，表示對於 `a` 而言從 `b'` 開始的右邊建築物還沒比較過，因此回到上面說的 `monotonic stack` 處理方式進行查找。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    std::vector<int> leftmostBuildingQueries(std::vector<int> &heights, std::vector<std::vector<int>> &queries) {
        // highest 儲存每個建築物其右邊第一個比自身高的建築物 index
        std::stack<size_t> st;
        std::vector<int> highest(heights.size());
        for (size_t i = heights.size() - 1; i < heights.size(); --i) {
            while (!st.empty() && heights[i] > heights[st.top()]) {
                st.pop();
            }

            highest[i] = (st.empty()) ? -1 : st.top();
            st.push(i);
        }

        // 對 queries 進行處理，讓 queries[i][0] <= queries[i][1]
        for (auto &query : queries) {
            if (query[0] > query[1]) {
                std::swap(query[0], query[1]);
            }
        }

        // 創建 queries_idx 儲存 queries 的 index，對 queries_idx 以 queries[queries_idx[i]][1] 由小到大進行排序
        // 這樣做的目的是在於達到排序 queries 的同時又能取得該 queries 原本的 index
        // 例如原本 queries_idx[3] = 3，排序後 queries_idx[3] = 12，能得知 queries_idx[3] 原本在 queries 的 index 為 12
        std::vector<size_t> queries_idx(queries.size());
        std::iota(queries_idx.begin(), queries_idx.end(), 0); // 初始化 queries_idx 為 0, 1, 2, 3, ...
        std::sort(queries_idx.begin(), queries_idx.end(), [&](size_t a, size_t b) {
            return queries[a][1] < queries[b][1];
        });

        // 用 map[i] 儲存曾經查詢過的 query(i, j) 的最新結果
        std::unordered_map<int, int> mp;
        std::vector<int> res(queries.size(), -1);
        for (size_t i = 0; i < queries.size(); ++i) {
            size_t idx = queries_idx[i]; // 該 query 在 queries 的 index
            int a = queries[idx][0];     // Alice 所在的建築物 index
            int b = queries[idx][1];     // Bob 所在的建築物 index

            // 第一和第二種情況，a 能直接到達 b 的位置
            if (a == b || heights[a] < heights[b]) {
                res[idx] = b;
                continue;
            }

            // 第三種情況，a 不能直接到達 b 的位置
            int j = highest[b];
            // 判斷 mp[a] 是否存在
            if (mp.find(a) != mp.end()) {
                // 如果 mp[a] 或 j 其中一個為 -1 表示無解
                // 反之判斷 mp[a] 和 j 誰比較大，mp[a] >= j 則直接用 mp[a] 為解，反之用 j 來往右找解
                j = (mp[a] == -1 || j == -1) ? -1 : std::max(j, mp[a]);
            }

            while (j > 0 && heights[j] <= heights[a]) {
                j = highest[j];
            }

            res[idx] = j;
            mp[a] = res[idx];
        }

        return res;
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241222205114218.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241222205114218.png)

#### 複雜度分析

令 $n$ 為 `heights` 長度、 $q$ 為 `queries` 長度。

- 時間複雜度： $O(q \cdot n)$

    計算 `highest` 需要 $O(n)$ ，對 `queries` 進行處理需要 $O(q)$ ，對 `queries_idx` 進行排序需要 $O(q \log q)$ ，對 `queries` 進行查詢需要 $O(q \cdot n)$ ，總共需要 $O(n + q + q \log q + q \cdot n)$ = $O(q \cdot n)$ 。

- 空間複雜度： $O(n + q)$

    計算 `highest` 需要 $O(n)$ ，`queries_idx` 需要 $O(q)$ ，`mp` 需要 $O(n)$ ，總共需要 $O(2 \cdot n + q)$ = $O(n + q)$ 。

### 2. Monotonic Stack and Binary Search （離線處理）

對於方法一的演算法可以進一步優化，先對每個 `queries[qi]` 的 `a` 和 `b` 做比較交換使 $a \leq b$ ，接著將 `queries` 分類，如果 `queries[qi]` 能直接回答答案就填入 `res[qi]`，不能直接回答答案的 `queries[qi]` 則將 `{heights[a], qi}` 存入一個 1D array `v` 的 `v[b]` 中，這樣 `v[b]` 就會有 `heights[a]`、`b`、在 `queries` 中的 index `qi` 三個資訊。

接著從 `heights` 最右邊往左遍歷，為何要從右往左遍歷呢?因為需要維護一個 `monotonic stack`，如果是左到右則每次迭代都需要**重新**建構，時間複雜度從 $O(n)$ 變為 $O(n^2)$ 。令當前遍歷的 index 為 `hi`、`heights` 長度為 `n`，每次遍歷時都維護一個範圍是 $[hi, n-1]$ 的 `monotonic stack` `st` ，`st` 裡面存放的資料是所有在 `heights[hi]` 右邊且比 `heights[hi]` 高的建築物 index，堆底到堆頂是嚴格遞減，每次迭代時將 `v[hi]` 裡面的資料取出，令 `ha` 為 `v[hi][0]` 也就是 `heights[a]`、`qi` 為 `v[hi][1]` 也就是這個 query 在 `queries` 中的 index，對 `st` 進行 `binary search` 查找 `st` 中比 `ha` 高且 index 最小的建築物，如果找到則將答案填入 `res[qi]`，找不到則 `res[qi]` 為 -1。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    std::vector<int> leftmostBuildingQueries(std::vector<int> &heights, std::vector<std::vector<int>> &queries) {
        std::vector<int> res(queries.size(), -1);
        // v 存放需要額外進行查找的 query 資訊
        std::vector<std::vector<std::pair<int, int>>> v(heights.size());
        for (size_t i = 0; i < queries.size(); ++i) {
            int a = queries[i][0], b = queries[i][1];
            if (a > b) {
                std::swap(a, b);
            }
            // 第一和第二種情況，a 能直接到達 b 的位置
            if (a == b || heights[a] < heights[b]) {
                res[i] = b;
            }
            else {
                // 第三種情況，a 不能直接到達 b 的位置，需要額外進行查找
                v[b].push_back({heights[a], i});
            }
        }

        std::vector<int> st;
        // 為了簡單地維護 monotonic stack，需要從右到左遍歷 heights
        for (size_t i = heights.size() - 1; i < heights.size(); --i) {
            // 對每個 query 進行 binary search
            for (auto &[ha, idx] : v[i]) {
                int l = 0, r = st.size() - 1;
                while (l <= r) {
                    int mid = l + (r - l) / 2;
                    if (heights[st[mid]] > ha) {
                        l = mid + 1;
                    }
                    else {
                        r = mid - 1;
                    }
                }
                // 如果有找到比 ha 大的，l = mid + 1，如果 l 是 0 代表找不到比 ha 大的
                res[idx] = (l == 0) ? -1 : st[l - 1];

                // C++20 的 binary search，主要用於找到第一個大於等於 ha 的元素，並返回其迭代器
                // auto it = std::ranges::lower_bound(st, -ha, {}, [&](int j) {
                //     return -heights[j];
                // });
                // res[idx] = it > st.begin() ? *prev(it) : -1;
            }

            // 維護 monotonic stack
            while (!st.empty() && heights[i] >= heights[st.back()]) {
                st.pop_back();
            }
            st.push_back(i);
        }

        return res;
    }
};
```

對於 `binary search` 也能改用 `stl` 中的 `std::ranges::lower_bound`

```cpp {.line-numbers}
int l = 0, r = st.size() - 1;
while (l <= r) {
    int mid = l + (r - l) / 2;
    if (heights[st[mid]] > ha) {
        l = mid + 1;
    }
    else {
        r = mid - 1;
    }
}
res[idx] = (l == 0) ? -1 : st[l - 1];
```

可以改成：

```cpp {.line-numbers}
auto it = std::ranges::lower_bound(st, -ha, {}, [&](int j){ return -heights[j]; });
res[idx] = it > st.begin() ? *prev(it) : -1;
```

需要注意的是不管是 `std::ranges::lower_bound` 還是 `std::ranges::upper_bound` 都是需要以**非嚴格遞增（允許重複值）**的序列進行搜尋，而 `st` 是嚴格遞減的，因此可以將 `ha` 和 `heights` 取負數後進行搜尋，比如原本 `ha` = 10，`heights` = {15, 13, 12 , 10, 9}，取負數後 `ha` = -10，`heights` = {-15, -13, -12, -10, -9}，此時 `heights` 就會變成了**嚴格遞增**的序列，可以改求**大於等於 `ha` 的第一個 element** 也就是 -10，然後再將回傳的`iterator` 往前推一個位置，這樣就能得到 `heights` 中比 `ha` 大的第一個 element 也就是 12。

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241222184401044.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241222184401044.png)

#### 複雜度分析

令 $n$ 為 `heights` 長度、 $q$ 為 `queries` 長度。

- 時間複雜度： $O(n + q \log n)$

    `v` 需要 $O(q)$ ，`st` 需要 $O(n)$ ，對 `v` 進行 `binary search` 需要 $O(q \log n)$ 。

- 空間複雜度： $O(n + q)$

    `v` 需要 $O(q)$ ，`st` 需要 $O(n)$

### 3. Priority Queue （離線處理）

和方法二的概念相似，遍歷 `heights` 依序將 `v[i]` 中的資料放入 `min heap` 的 `priority queue` `pq` 中，以 `ha` 為排序基準，top 為最小的 `ha`，每次迭代時將當前建築物 `i` 的高度和 `pq` 的 top 的 `ha` 比較，如果 $heights[i] > ha$ ，則 $res[qi] = i$ 。為何要依序將 `v[i]` 中的資料放入 `pq` 中呢?因為每個 query 的 `a`、`b` 都只能移動到 [b, n-1] 範圍中的建築物，如果一次將所有要查找的 query 都放入 `pq` 中，可能會導致當前遍歷的建築物 `i` 在 `b` 左邊卻因為 `i` 比 `a` 高導致錯誤填入答案，因此要依序將 `v[i]` 中的資料放入 `pq` 中。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    std::vector<int> leftmostBuildingQueries(std::vector<int> &heights, std::vector<std::vector<int>> &queries) {
        std::vector<int> res(queries.size(), -1);
        // v 存放需要額外進行查找的 query 資訊
        std::vector<std::vector<std::pair<int, int>>> v(heights.size());
        for (size_t i = 0; i < queries.size(); ++i) {
            int a = queries[i][0], b = queries[i][1];
            if (a > b) {
                std::swap(a, b);
            }
            // 第一和第二種情況，a 能直接到達 b 的位置
            if (a == b || heights[a] < heights[b]) {
                res[i] = b;
            }
            else {
                // 第三種情況，a 不能直接到達 b 的位置，需要額外進行查找
                v[b].push_back({heights[a], i});
            }
        }

        // min heap
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> pq;
        for (size_t i = 0; i < heights.size(); ++i) {
            // 如果當前建築物 i 比 pq top 的 a 還要高，則 i 就是答案
            while (!pq.empty() && pq.top().first < heights[i]) {
                res[pq.top().second] = i;
                pq.pop();
            }

            // 不能一次將所有要查詢的資料全部加入 pq，如果 i 在 b 左邊時會出錯
            // 每個 query 只能和 b 右邊的建築來比較
            for (std::pair<int, int> &query : v[i]) {
                pq.push(query);
            }
        }

        return res;
    }
};

```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241222202009223.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241222202009223.png)

#### 複雜度分析

令 $n$ 為 `heights` 長度、 $q$ 為 `queries` 長度。

- 時間複雜度： $O(n + q \log q)$

    `v` 需要 $O(q)$ ，遍歷 `heights` 需要 $O(n)$ ，每個 query 加入彈出 `pq` 需要 $O(q \log q)$ 。

- 空間複雜度： $O(n + q)$ 。
