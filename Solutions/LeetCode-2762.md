# <center> [LeetCode - 2762. Continuous Subarrays](https://leetcode.com/problems/continuous-subarrays/description/) </center>

## 題目敘述

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241214175430567.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241214175430567.png)

給一個 integer array `nums`，找出所有 `continuous` subarray 並回傳數量。

`continuous` subarray 的定義為：

- subarray 是連續且非空的子序列

- 對於 index : $i \leq i_1, i_2 \leq j$ 的 subarray，滿足 $abs(nums[i_1] - nums[i_2] \leq 2)$

e.g.

`nums` = {5, 4, 3, 3, 2, 4}

- 長度為 1 的 `continuous` subarray 有 6 個：{5}, {4}, {3}, {3}, {2}, {4}

- 長度為 2 的 `continuous` subarray 有 5 個：{5, 4}, {4, 3}, {3, 3}, {3, 2}, {2, 4}

- 長度為 3 的 `continuous` subarray 有 4 個：{5, 4, 3}, {4, 3, 3}, {3, 3, 2}, {3, 2, 4}

- 長度為 4 的 `continuous` subarray 有 3 個：{5, 4, 3, 3}, {4, 3, 3, 2}, {3, 3, 2, 4}

- 長度為 5 的 `continuous` subarray 有 1 個：{4, 3, 3, 2, 4}

- 長度為 6 的 `continuous` subarray 有 0 個：

總共為 19 個。

## 解題思路

### 1. Sliding Window and Hash Map

用 `hash map` 紀錄目前 window 內的數字，並用 `left` 和 `right` 兩個 pointer 來維護 window 的範圍，當 `hash map` 內的最大值和最小值相差超過 2 時，將 `left` 往右移動，直到 `hash map` 內的最大值和最小值相差小於等於 2 為止。

而要計算 `continuous subarray` 的數量，可以累加 `right - left + 1` 的值，如下舉例:

`nums` = {1,2,3}，此時所有可能的 subarray 有 {{1}, {2}, {3}, {1, 2}, {2, 3}, {1, 2, 3}}，共 6 個。

當加進來一個新的數字 4 時，數字 4 可以選擇不和前面的數字組成 subarray，也可以選擇和前面連續 1、2、3 個數字組成 subarray，因此多出來的 subarray 組合就會是加入數字 4 後當前 array 的長度。

新增的 subarray 組合有: {{4}, {3, 4}, {2, 3, 4}, {1, 2, 3, 4}}，共 4 個。

完整的操作流程如下：

`nums` == {5, 4, 3, 3, 2, 4}

- 當 `left` 為 0，`right` 為 0 時，`hash map` 內的數字為 {5}，最大值和最小值相差 0，`continuous` subarray 的數量為 (r - l + 1) = 1。

- 當 `left` 為 0，`right` 為 1 時，`hash map` 內的數字為 {5, 4}，最大值和最小值相差 1，`continuous` subarray 的數量為 (r - l + 1) = 2。

- 當 `left` 為 0，`right` 為 2 時，`hash map` 內的數字為 {5, 4, 3}，最大值和最小值相差 2，`continuous` subarray 的數量為 (r - l + 1) = 3。

- 當 `left` 為 0，`right` 為 3 時，`hash map` 內的數字為 {5, 4, 3, 3}，最大值和最小值相差 2，`continuous` subarray 的數量為 (r - l + 1) = 4。

- 當 `left` 為 0，`right` 為 4 時，`hash map` 內的數字為 {5, 4, 3, 3, 2}，最大值和最小值相差 3，將 `left` 往右移動直到最大最小值相差不超過 2，此時 `left` 為 1，`continuous` subarray 的數量為 (r - l + 1) = 4。

- 當 `left` 為 1，`right` 為 5 時，`hash map` 內的數字為 {4, 3, 3, 2, 4}，最大值和最小值相差 2，`continuous` subarray 的數量為 (r - l + 1) = 5。

將這些數量加總起來，即可得到 `continuous` subarray 的總數量為 19。

#### 程式碼

```c++ {.line-numbers}
class Solution {
  public:
    long long continuousSubarrays(std::vector<int> &nums) {
        size_t l = 0, r = 0, n = nums.size(); // l 和 r 為當前 window 的範圍
        long long res = 0;
        std::map<int, int> window; // 用於儲存 window 中所有 element 的出現次數，最多只會有四個 element

        for (; r < n; ++r) {
            ++window[nums[r]];
            // begin() 為 map 第一個 element 也是最小值，rbegin() 為 map 的最後一個 element 也是最大值
            while (window.rbegin()->first - window.begin()->first > 2) {
                // 將 window 往右縮小，最左邊的 element 次數減 1
                --window[nums[l]];
                // 如果 element 的出現次數為 0，將其從 map 中刪除以維護最大最小值
                if (window[nums[l]] == 0) {
                    window.erase(nums[l]);
                }
                ++l;
            }
            // 累加當前 subarray 的長度
            res += r - l + 1;
        }

        return res;
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241214193328225.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241214193328225.png)

#### 複雜度分析

令 $n$ 為 `nums` 的長度， $k$ 為 `hash map` 內的 element 數量。

- 時間複雜度： $O(n)$

    原本為 $O(n \log k)$ ，由於最多只會有 4 個 element，因此 $k$ 為常數，故時間複雜度最終為 $O(n)$。

- 空間複雜度： $O(1)$

    原本為 $O(k)$ ，由於最多只會有 4 個 element，因此 $k$ 為常數，故空間複雜度最終為 $O(1)$。

### 2. Sliding Window and Multiset

一樣的概念，只是將 `hash map` 改成 `multiset` 來儲存 window 內的數字。

#### 程式碼

```c++ {.line-numbers}
class Solution {
  public:
    long long continuousSubarrays(std::vector<int> &nums) {
        size_t l = 0, r = 0, n = nums.size(); // l 和 r 為當前 window 的範圍
        long long res = 0;
        std::multiset<int> window; // 用於儲存 window 中所有 element，如果 element 都一樣大則最多會有 n 個

        for (; r < n; ++r) {
            window.insert(nums[r]);
            // begin() 為 multiset 第一個 element 也是最小值，rbegin() 為 multiset 的最後一個 element 也是最大值
            while (*window.rbegin() - *window.begin() > 2) {
                // 將 window 往右縮小，刪除最左邊的 element
                window.erase(window.find(nums[l++]));
            }
            // 累加當前 subarray 的長度
            res += r - l + 1;
        }

        return res;
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241214183416675.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241214183416675.png)

#### 複雜度分析

令 $n$ 為 `nums` 的長度， $k$ 為 `multiset` 內的 element 數量。

- 時間複雜度： $O(n \log n)$

    原本為 $O(n \log k)$ ，由於最多只會有 $n$ 個 element，因此時間複雜度最終為 $O(n \log n)$。

- 空間複雜度： $O(n)$

    原本為 $O(k)$ ，由於最多只會有 $n$ 個 element，因此空間複雜度最終為 $O(n)$。

### 3. Sliding Window and Priority Queue

也是一樣的概念，只是將 `hash map` 改成 `priority queue` 來儲存 window 內的數字。

#### 程式碼

```c++ {.line-numbers}
class Solution {
  public:
    long long continuousSubarrays(std::vector<int> &nums) {
        size_t l = 0, r = 0, n = nums.size(); // l 和 r 為當前 window 的範圍
        long long res = 0;
        std::deque<int> qmax, qmin; // 用於儲存當前 window 的最大值和最小值

        for (; r < n; ++r) {
            // 維護 qmax 和 qmin 的單調性
            while (!qmax.empty() && qmax.back() < nums[r]) {
                qmax.pop_back();
            }
            qmax.push_back(nums[r]);
            while (!qmin.empty() && qmin.back() > nums[r]) {
                qmin.pop_back();
            }
            qmin.push_back(nums[r]);

            // 如果當前 window 的最大值和最小值的差大於 2，則向右移動 l 指針，直到滿足條件
            while (qmax.front() - qmin.front() > 2) {
                // 移動 l 指針時，更新 qmax 和 qmin
                if (qmax.front() == nums[l]) {
                    qmax.pop_front();
                }
                if (qmin.front() == nums[l]) {
                    qmin.pop_front();
                }
                ++l;
            }

            res += r - l + 1;
        }

        return res;
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241214184944790.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241214184944790.png)

#### 複雜度分析

令 $n$ 為 `nums` 的長度。

- 時間複雜度： $O(n)$

    每個 element 最多被 push 和 pop 一次，因此時間複雜度為 $O(n)$ 。

- 空間複雜度： $O(n)$

    `qmax` 和 `qmin` 最多只會有 $n$ 個 element，因此空間複雜度為 $O(n)$ 。

### 4. Sliding Window

不用任何資料結構，直接使用 `sliding window` 來維護當前 window 的最大值和最小值。

#### 程式碼

```c++ {.line-numbers}

class Solution {
  public:
    long long continuousSubarrays(std::vector<int> &nums) {
        size_t l = 0, r = 0, n = nums.size();     // l 和 r 為當前 window 的範圍
        int max_val = nums[0], min_val = nums[0]; // 紀錄當前 window 的 max 和 min
        long long res = 0;

        for (; r < n; ++r) {
            // 更新 max and min
            max_val = std::max(max_val, nums[r]);
            min_val = std::min(min_val, nums[r]);

            // 如果 max - min > 2 則需要縮小 window
            if (max_val - min_val > 2) {
                if (nums[r] == max_val) {
                    min_val = max_val - 2;
                    int lower_bound = min_val - 1;
                    l = r;
                    // 從 r 開始往左找，找到第一個小於 max_val - 2 的數
                    // 則從該數左邊到 r 之間的數都是符合條件的
                    while (nums[l] > lower_bound) {
                        --l;
                    }
                }
                else {
                    max_val = min_val + 2;
                    int uppper_bound = max_val + 1;
                    l = r;
                    // 從 r 開始往左找，找到第一個大於 min_val + 2 的數
                    // 則從該數左邊到 r 之間的數都是符合條件的
                    while (nums[l] < uppper_bound) {
                        --l;
                    }
                }
                // 因為找到的是第一個大於 max_val - 2 或小於 min_val + 2 的數
                // 所以 l 要往右移一格才是現在 window 的範圍
                ++l;
            }

            // 累加當前 continuous subarray 的 長度
            res += r - l + 1;
        }

        return res;
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241214192340223.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241214192340223.png)

#### 複雜度分析

令 $n$ 為 `nums` 的長度。

- 時間複雜度： $O(n)$

    每個 element 最多遍歷一次，因此時間複雜度為 $O(n)$ 。

- 空間複雜度： $O(1)$
