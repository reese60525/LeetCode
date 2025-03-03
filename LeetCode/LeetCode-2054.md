# <center> [2054. Two Best Non-Overlapping Events](https://leetcode.com/problems/two-best-non-overlapping-events/description/) </center>

## 題目敘述

[![](https://i.imgur.com/WCxpjst.png)](https://i.imgur.com/WCxpjst.png)

給一個二維整數陣列 `events` ， $events[i] = [startTime_i, endTime_i, value_i]$ 分別表示第 `i` 個事件的開始時間、結束時間和價值。找出 **最多兩個 startTime 和 endTime 不重疊** 的事件，使其 $value_1 + value_2$ 為最大值並回傳。

- 可以只選擇零個或是一個事件。

重疊的定義：

考慮 `events[i]` 和 `events[j]`，如果 $startTime_i \leq startTime_j \leq endTime_i$ 或是 $startTime_i \leq endTime_j \leq endTime_i$ ，則 `events[i]` 和 `events[j]` 是重疊的。

e.g.

**下面的例子對於每個事件，只考慮其後方事件，前面已經配對過的事件就不重複計算了。**

1. $events = [[1, 3, 2], [4, 5, 2], [2, 4, 3]]$

   - 對於 `events[0]`，可以選擇 `events[1]` 來配對， $\max(value_0 + value_1) = \max(2 + 2) = 4$ 。

   - 對於 `events[1]`，後面沒有其他事件能與它配對， $maxValue = value_1 = 2$ 。

   - 對於 `events[2]`，後面沒有其他事件能與它配對， $maxValue = value_2 = 3$ 。

   因此答案為 $\max(4, 2, 3) = 4$ 。

2. $events = [[1, 3, 2], [4, 5, 2], [1, 5, 5]]$

    - 對於 `events[0]`，可以選擇 `events[1]` 來配對， $\max(value_0 + value_1) = \max(2 + 2) = 4$ 。

    - 對於 `events[1]`，後面沒有其他事件能與它配對， $maxValue = value_1 = 2$ 。

    - 對於 `events[2]`，後面沒有其他事件能與它配對， $maxValue = value_2 = 5$ 。

   因此答案為 $\max(4, 2, 5) = 5$ 。

## 解題思路

### 1. Dynamic Programming and Binary Search

這題的關鍵在於如何找到兩個不重疊的事件，可以先將 `events` 按照 `startTime` 由小到大排序，接著遍歷 `events`，對於 `events[i]`，用 binary search 找到 `events[i]` 後面所有事件中 $startTime_j > endTime_i$ （也就是和 `events[i]` 不重疊的 events）的最小 index `j`，則從 `events[j]` 開始的 events 都是可以和 `events[i]` 配對的，選擇其中 $value_j$ 最大的事件和 `events[i]` 配對，為此需要建立一個整數陣列 `dp` 來儲存在 $index = j$ 時 `events[j]` 和後面所有事件的 $\max(value_j)$ 。當遍歷完 `events` 後就能得到答案。

比較有趣的一點是在排序 `events` 時，如果是使用 `lambda` 表達式來排序，會發現這樣的排序效率更高，原因是因為 `std::sort` 預設的排序方式會將 `events` 中三個 element 都進行比較，而使用 `lambda` 表達式排序則只會將 `endTime` 進行排序，這樣可以減少排序的時間，進而提高效能。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    int maxTwoEvents(std::vector<std::vector<int>> &events) {
        // 將所有 events 依照 start time 由小到大排序
        std::sort(events.begin(), events.end(), [](const std::vector<int> &a, const std::vector<int> &b) {
            return a[0] < b[0];
        });

        // 計算每個 events[i] 從其本身到後面所有 events 的最大值
        std::vector<int> dp(events.size());
        dp[events.size() - 1] = events[events.size() - 1][2];
        // 從倒數第二個 events 開始往前計算
        for (int i = events.size() - 2; i >= 0; --i) {
            dp[i] = std::max(events[i][2], dp[i + 1]);
        }

        int res = 0;
        for (int i = 0; i < events.size(); ++i) {
            // 用 binary search 查找 events[i] 後面是否有能配對的 events
            int l = i + 1, r = events.size();
            while (l < r) {
                int mid = l + (r - l) / 2;
                // 若是當前 events[mid] 的 start time 大於 events[i] 的 end time 的話
                // 表示 mid 右邊的 events 都能和 events[i] 配對，所以往左繼續找更多能配對的 events
                if (events[mid][0] > events[i][1]) {
                    r = mid; // mid 有可能就是 events[i] 所能配對的第一個 events，不能用 mid - 1
                }
                else {
                    l = mid + 1;
                }
            }

            // 檢查 events[i] 後面是否有能配對的 events，如果沒有則 l 會等於 events.size()
            if (l < events.size()) {
                // 若有能配對的 events，則將 events[i] 和其所能配對到的 events 最大值的和與 res 比較
                res = std::max(res, events[i][2] + dp[l]);
            }
            else {
                // 若沒有能配對的 events，則將 events[i] 的值與 res 比較
                res = std::max(res, events[i][2]);
            }
        }

        return res;
    }
};
```

[![](https://i.imgur.com/4teMXaB.png)](https://i.imgur.com/4teMXaB.png)

#### 複雜度分析

令 $n$ 為 `events` 的長度。

- 時間複雜度： $O(n \cdot \log n)$

- 空間複雜度： $O(n)$

### 2. Priority Queue

思路和第一個解法大致相同，將 `events` 以 `startTime` 由小到大排序，並建立一個以 `endTime` 排序的 min heap 的 priority queue `pq` 來儲存所有事件的 `endTime` 和 `value`。遍歷 `events`，`pre_max` 表示當前 `event[i]` 的前面所有能配對的事件的 `value` 的最大值，對於 `events[i]` 如果 `pq top` 的 $endTime_{pq} < startTime_i$ ，則表示 `pq top` 的 event 能和 `events[i]` 配對，將 `pq top` 和 `pre_max` 比對取最大值然後將 `pq top` 彈出，直到 `pq top` 的 $endTime_{pq} \geq startTime_i$ 或 `pq` 為空，而這個 `pre_max` 就是 `events[i]` 能配對到的最大值，將其和 `events[i]` 的 `value` 相加後和 `res` 比較取最大值，遍歷完後 `res` 就是答案。

對於 `pq` 的處理原本是先將所有 `events` 的 `endTime` 和 `value` 都 push 進 `pq` 中，對於這種方式可以進一步優化，先不將任何資料 push 進 `pq` 中，而是遍歷 `events` 的過程中，如果 $value_i > pre\_max$ 時，再將 `events[i]` 的 `endTime` 和 `value` push 進 `pq` 中，讓不可能比 `pre_max` 的事件直接略過不用比較，這樣可以減少操作 `pq` 的次數，進而提升效率。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    typedef std::pair<int, int> PII;
    int maxTwoEvents(std::vector<std::vector<int>> &events) {
        // 將所有 events 依照 start time 由小到大排序
        std::sort(events.begin(), events.end(), [](const std::vector<int> &a, const std::vector<int> &b) {
            return a[0] < b[0];
        });

        // pre_max 用來紀錄目前 event[i] 之前的最大 event value
        int res = 0, pre_max = 0;
        // 建立 以 endTime 排序 min heap priority queue
        std::priority_queue<PII, std::vector<PII>, std::greater<PII>> pq;
        // 遍歷 events 找最大值
        for (auto &event : events) {
            // 將 pq 中的 event 與當前 event[i] 不重疊則進去更新 pre_max
            while (!pq.empty() && pq.top().first < event[0]) {
                // 更新 pre_max
                pre_max = std::max(pre_max, pq.top().second);
                pq.pop();
            }

            // 更新 res
            res = std::max(res, event[2] + pre_max);

            // 如果 event[i] 的 value 比 pre_max 大，則將 event[i] 加入 pq
            if (event[2] > pre_max) {
                pq.push({event[1], event[2]});
            }
        }

        return res;
    }
};
```

[![](https://i.imgur.com/gZcFvwU.png)](https://i.imgur.com/gZcFvwU.png)

#### 複雜度分析

令 $n$ 為 `events` 的長度。

- 時間複雜度： $O(n \cdot \log n)$

- 空間複雜度： $O(n)$

### 3. Sorting and Greedy

將 `events` 中的 `startTime` 和 `endTime` 各自拆開，用 $Tuple = [time, is\_end, value]$ 的形式存到 `times` 這個陣列中，並且將 `times` 進行排序。`pre_max` 用來表示當前遇到的最大 `value`，遍歷 `times`，如果 $is\_end = true$ 則表示這個 event 結束了，將 `pre_max` 更新為 $pre\_max = \max(pre\_max, value_i)$ ，如果 $is\_end = false$ 則表示這個 event 開始了，將 `res` 更新為 $res = \max(res, pre\_max)$ ，遍歷完 `times` 後 `res` 就是答案。

需要注意的是 `tuple` 的資料結構順序很重要，因為預設的 `std::sort` 會先排序 `time`，如果 `time` 一樣就會比較 `is_end`，而 `bool` 的排序會是 `false` 優先於 `true`，因此如果 `time` 一樣的話， $is\_end = false$ 的會排在前面， $is\_end = true$ 的會排在後面，這樣才能保證 `pre_max` 的更新順序是正確的，也就是在遍歷 `times` 的過程中，如果 `time` 相同，一定會先遇到 $is\_end = false$ 的 `tuple`，`pre_max` 會先被更新，然後才會遇到 $is\_end = true$ 的 `tuple`，這樣子在更新 `res` 才會是正確的。

#### 程式碼

```c++ {.line-numbers}
class Solution {
  public:
    typedef std::tuple<int, bool, int> info; // <time, value, is_end>
    int maxTwoEvents(std::vector<std::vector<int>> &events) {
        // 將 startTime 和 endTime 拆開，並放入同個 array 中
        std::vector<info> times(2 * events.size());
        for (int i = 0; i < events.size(); ++i) {
            int start = events[i][0], end = events[i][1], value = events[i][2];
            times[2 * i] = {start, false, value};
            times[2 * i + 1] = {end, true, value};
        }

        // 將 times 依照進行排序
        std::sort(times.begin(), times.end());

        int res = 0, pre_max = 0;
        for (auto &[time, is_end, value] : times) {
            // 如果 time 是 endTime，代表該 event 已經結束，更新 pre_max
            if (is_end) {
                pre_max = std::max(pre_max, value);
            }
            // 如果 time 是 startTime，代表該 event 開始，更新 res
            else {
                res = std::max(res, pre_max + value);
            }
        }

        return res;
    }
};
```

[![](https://i.imgur.com/mM5MEEQ.png)](https://i.imgur.com/mM5MEEQ.png)

#### 複雜度分析

令 $n$ 為 `events` 的長度。

- 時間複雜度： $O(n \cdot \log n)$

- 空間複雜度： $O(n)$
