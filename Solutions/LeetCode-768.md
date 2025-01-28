# <center> [LeetCode - 768. Max Chunks To Make Sorted II](https://leetcode.com/problems/max-chunks-to-make-sorted-ii/description/) </center>

## 題目敘述

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures202412191435756.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures202412191435756.png)

給一個整數陣列 `arr`，將其進行以下操作:

1. 將 `arr` 分割成一個或多個 subarray

2. 對每個 subarray 進行排序

3. 將每個 subarray 合併成一個 sorted array

4. 合併後的 sorted array 必須是**非遞減排序**

請找出經過以上操作後，subarray 所能達到的最大數量。

e.g.

$arr = [1, 2, 3, 1, 1, 2, 3, 4, 3]$

- 可以將 `arr` 分割成 `[[1], [2, 3, 1, 1, 2], [3], [4, 3]]`，排序後變成 `[[1], [1, 1, 2, 2, 3], [3], [3, 4]]`，合併後為 `[1, 1, 1, 2, 2, 3, 3, 3, 4]`，subarray 數量為 4。

- 可以將 `arr` 分割成 `[[1, 2, 3, 1, 1, 2, 3], [4, 3]]`，排序後變成 `[[1, 1, 1, 2, 2, 3, 3], [3, 4]]`，合併後為 `[1, 1, 1, 2, 2, 3, 3, 3, 4]`，subarray 數量為 2。

- 以此類推...可以得到 subarray 最大數量為 4。

## 解題思路

### 1.  Monotonic Stack

假設我們有 `k` 個 subarray：`[[sbu_1], [sub_2], [sub_3], ...,[sub_k]]`，`max[i]` 為第 `i` 個 subarray 的最大值，如果這時候新增了一個 value `x`，會有兩種情況：

1. $x \geq max[k]$ ，`x` 可以自己成為一個新的 subarray，subarray 數量 + 1，變成 `[[sub_1], [sub_2], [sub_3], ...,[sub_k], [x]]`。

2. $x < max[k]$ ，`x` 不能自己成為一個新的 subarray，因為 $x < max[k]$ ，此時將所有 subarray 排序並且合併後的 `sorted array` 不會是**非遞減排序**，因此要將 `x` 和左邊**所有** $max[i] > x$ 的 subarray 合併成一個新的 subarray，為何要這樣做呢？舉個例子假設有這樣的 subarray：`[[1, 2, 3], [4, 5, 6], [7, 8, 9]]`，將 3 加入，如果只將 3 和 `[7, 8, 9]` 合併，那麼排序且合併所有 subarray 後的結果會是 `[1, 2, 3, 4, 5, 6, 3, 7, 8, 9]`，`sorted array` 不會是**非遞減排序**，因此要繼續往左邊找，直到找到一個 subarray 的 $max[i] \leq x$ 為止，將這些 $max[i] > x$ 的 subarray 和 `x` 合併形成新的 subarray，這樣產生的 `sorted array` 才會是**非遞減排序**，以這個例子來看需要將`[[4, 5, 6], [7, 8, 9]]` 和 3 合併成 `[4, 5, 6, 7, 8, 9, 3]`。

因此我們可以維護一個**單調遞增**的 stack，stack 存放每個 subarray 的 `max_val`，遍歷 `arr`，當新增一個 element `x` 時，如果 `x` 大於等於 stack `top`，該 `x` 能自己形成 subarray，將 `x` 加入 stack 中，否則不斷將 stack `top` pop，直到 $top \leq x$ ，這些被 pop 的 subarray 和 `x` 合併成一個新的 subarray，並將新的 subarray 的 `max_val` 加入 stack 中，最後 stack 中所有 element 的數量就是 subarray 的最大數量。

e.g.

$arr = [1, 2, 3, 1, 1, 2, 3, 4, 3, 2]$ ， $stack = []$

- `stack` 為空，將 1 加入 stack 中， $stack = [1]$

- $arr[1] = 2 \geq top = 1$ ，將 2 加入 stack 中， $stack = [1, 2]$

- $arr[2] = 3 \geq top = 2$ ，將 3 加入 stack 中， $stack = [1, 2, 3]$

- $arr[3] = 1 < top = 3$ ，將 `stack` pop 直到 $top \leq 1$ ，然後把新的 subarray $max\_val = 3$ 加入 `stack`， $stack = [1, 3]$

- $arr[4] = 1 < top = 3$ ，將 `stack` pop 直到 $top \leq 1$ ，然後把新的 subarray $max\_val = 3$ 加入 `stack`， $stack = [1, 3]$

- $arr[5] = 2 < top = 3$ ，將 `stack` pop 直到 $top \leq 2$ ，然後把新的 subarray $max\_val = 3$ 加入 `stack`， $stack = [1, 3]$

- $arr[6] = 3 \geq top = 3$ ，將 3 加入 stack 中， $stack = [1, 3, 3]$

- $arr[7] = 4 \geq top = 3$ ，將 4 加入 stack 中， $stack = [1, 3, 3, 4]$

- $arr[8] = 3 < top = 4$ ，將 `stack` pop 直到 $top \leq 3$ ，然後把新的 subarray $max\_val = 4$ 加入 `stack`， $stack = [1, 3, 3, 4]$

- $arr[9] = 2 < top = 4$ ，將 `stack` pop 直到 $top \leq 2$ ，然後把新的 subarray $max\_val = 4$ 加入 `stack`， $stack = [1, 4]$

- 遍歷完 `arr`，`stack` 中所有 element 的數量為 2，因此 subarray 的最大數量為 2。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    int maxChunksToSorted(std::vector<int> &arr) {
        std::stack<int> st;

        for (int n : arr) {
            // n 無法自己成為 subarray，需要將所有 max_val > n 的 subarray 合併
            if (!st.empty() && st.top() > n) {
                // 紀錄新 subarray 的 max value，正好是當前的 top
                int max_val = st.top();
                while (!st.empty() && st.top() > n) {
                    st.pop();
                }
                st.push(max_val);
            }
            // n 能自己成為 subarray，直接 push 到 stack
            else {
                st.push(n);
            }
        }

        return st.size();
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241219183530320.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241219183530320.png)

#### 複雜度分析

令 $n$ 為 `arr` 的長度。

- 時間複雜度： $O(n)$

- 空間複雜度： $O(n)$

### 2. Prefix Max and Suffix Min

基於方法 1 的推導，令 `arr` 長度為 `n`，可以發現在 $index = i$ 時，如果 `[0, i]` 之間的 $maxVal \leq [i+1,n-1] \text{之間的} minVal$ ，則 `arr[i]` 可以自己成為一個 subarray，能在 `i` 和 `i+1` 之間分割成兩部分。

創建一個 `prefixMax` 和 `suffixMin` 來記錄每個 index 的 prefix max value 和 suffix min value，遍歷 `arr` 判斷 $prefixMax[i] \leq suffixMin[i+1]$ ，要注意的是只要遍歷到 `arr[n-2]` 也就是 $index = n - 2$ 即可，因為 $index = n - 1$ 時，`arr[n-1]` 右邊沒有可以比較的 `suffixMin`。

e.g.

$arr = [2, 1, 5, 2, 3, 4, 7, 8]$ ， $prefixMax = [2, 2, 5, 5, 5, 5, 7, 8]$ ， $suffixMin = [1, 1, 2, 2, 3, 4, 7, 8]$

- $index = 0$ ， $prefixMax[0] = 2 > suffixMin[1] = 1$ ，`arr[0]` 無法自己成為一個 subarray。

- $index = 1$ ， $prefixMax[1] = 2 \leq suffixMin[2] = 2$ ，`arr[1]` 可以自己成為一個 subarray，在 $index = 1$ 和 $index = 2$ 之間分割成兩部分， $arr = [[2, 1], [5, 2, 3, 4, 7, 8]]$ 。

- $index = 2$ ， $prefixMax[2] = 5 > suffixMin[3] = 2$ ，`arr[2]` 無法自己成為一個 subarray。

- $index = 3$ ， $prefixMax[3] = 5 > suffixMin[4] = 3$ ，`arr[3]` 無法自己成為一個 subarray。

- $index = 4$ ， $prefixMax[4] = 5 > suffixMin[5] = 4$ ，`arr[4]` 無法自己成為一個 subarray。

- $index = 5$ ， $prefixMax[5] = 5 \leq suffixMin[6] = 7$ ，`arr[5]` 可以自己成為一個 subarray，在 $index = 5$ 和 $index = 6$ 之間分割成兩部分， $arr = [[2, 1], [5, 2, 3, 4], [7, 8]]$ 。

- $index = 6$ ， $prefixMax[6] = 7 \leq suffixMin[7] = 8$ ，`arr[6]` 可以自己成為一個 subarray，在 $index = 6$ 和 $index = 7$ 之間分割成兩部分， $arr = [[2, 1], [5, 2, 3, 4], [7], [8]]$ 。

- $index = 7$ ， 沒有可以比較的 `suffixMin`，結束遍歷。 $arr = [[2, 1], [5, 2, 3, 4], [7], [8]]$ ，因此 subarray 的最大數量為 4。

[圖片來源](https://leetcode.cn/problems/max-chunks-to-make-sorted-ii/solutions/1744296/zui-duo-neng-wan-cheng-pai-xu-de-kuai-by-z0wz/)

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241219193336220.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241219193336220.png)

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241219193426384.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241219193426384.png)

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241219193443300.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241219193443300.png)

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241219193459398.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241219193459398.png)

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241219193510697.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241219193510697.png)

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241219193528245.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241219193528245.png)

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241219193542520.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241219193542520.png)

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241219193558083.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241219193558083.png)

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241219193611826.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241219193611826.png)

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    int maxChunksToSorted(std::vector<int> &arr) {
        size_t n = arr.size();
        std::vector<int> prefix_max(arr.size()), suffix_min(arr.size());
        // 紀錄 prefix_max 和 suffix_min
        for (size_t i = 0; i < n; ++i) {
            prefix_max[i] = (i == 0) ? arr[i] : std::max(prefix_max[i - 1], arr[i]);
            suffix_min[n - i - 1] = (i == 0) ? arr[n - 1] : std::min(suffix_min[n - i], arr[n - i - 1]);
        }

        int res = 0;
        // 用 arr[i] 的 prefix_max 和 arr[i+1] suffix_min 來判斷是否能形成 subarray
        // 因此只需要檢查到 arr[n-2] 即可，因為 arr[n-1] 沒有 suffix_min 可以比較
        for (size_t i = 0; i < n - 1; ++i) {
            res += (prefix_max[i] <= suffix_min[i + 1]);
        }

        // res 是分割線的數量，一個分割線可以分割出兩個 subarray
        // 因此 subarray 數量為 res + 1
        return res + 1;
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241219194324984.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241219194324984.png)

#### 複雜度分析

令 $n$ 是 `arr` 的長度。

- 時間複雜度： $O(n)$

- 空間複雜度： $O(n)$
