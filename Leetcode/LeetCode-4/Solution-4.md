# <center> [LeetCode - 4. Median of Two Sorted Arrays](https://leetcode.com/problems/median-of-two-sorted-arrays/description/) </center>

## 題目敘述

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241207203744788.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241207203744788.png)

給兩個已經排序的 integer array `nums1` and `nums2`，找出兩 array 合併後的中位數。  
**題目要求時間複雜度必須為 $O(log(m+n))$**

## 解題思路

### 1. Binary Search

#### 方法 1

時間複雜度必須為 $O(log(m+n))$，很明顯就是得用 binary search 來解。  
將該題目看成是找第 `k` 小的數，因為是要找中位數，所以 `k` 的值為 $\frac{m+n}{2}$，若 $m+n$ 為奇數，則 $k$ 為 $\frac{m+n}{2} + 1$。  
對於 `nums1` = {a1, a2, ... , an}，`nums2` = {b1, b2, ... , bm}，假設 $nums1[k/2] <= nums2[k/2]$，`nums1[0]` 到 `nums1[k/2]` 共 $\frac{k}{2}$ 個數，而 `nums2[0]` 到 `nums2[k/2 - 1]` 共有 $\frac{k}{2} -1$ 個數，兩者相加為 $k-1$ 個，因此第 `k` 小的數一定不會在 `nums1[0]` 到 `nums1[k/2]` 中，所以可以將 `nums1[0]` 到 `nums1[k/2]` 都刪除。  
因此每次都直接比較第 $\frac{k}{2}$ 的數，該數比較小的那一方，其左邊的數都會比第 `k` 小的數小，可以將該數和其左邊的數都刪除，並將 `k` 的值減去刪除的數的數量，每次都能刪除 $\frac{k}{2}$ 個數，時間複雜度為 $O(log(m+n))$。  

舉例來說:

1. `nums1` = {4, 5, 6, 7, 8, 9}，`nums2` = {1, 2, 8, 9, 10, 11, 12}， $k = \frac{6+7}{2} + 1 = 7$。  
    比較 $index = \frac{7}{2} -1 = 2$ 的數， $nums1[2] = 6 < nums2[2] = 7$，因此刪除 `nums1[2]` 和其左邊的數，`k` 的值減去刪除的數的數量， $k = 7 - 3 = 4$。  
2. `nums1` = {7, 8, 9}，`nums2` = {1, 2, 8, 9, 10, 11, 12}， $k = 4$。  
    $k = 4$，比較 $index = \frac{4}{2} -1 = 1$ 的數， $nums1[1] = 8 > nums2[1] = 2$，因此刪除 `nums2[1]` 和其左邊的數，`k` 的值減去刪除的數的數量， $k = 4 - 2 = 2$。  
3. `nums1` = {7, 8, 9}，`nums2` = {8, 9, 10, 11, 12}， $k = 2$。  
    $k = 2$，比較 $index = \frac{2}{2} -1 = 0$ 的數， $nums1[0] = 7 < nums2[0] = 8$，因此刪除 `nums1[0]` 和其左邊的數，`k` 的值減去刪除的數的數量， $k = 2 - 1 = 1$。  
4. `nums1` = {8, 9}，`nums2` = {8, 9, 10, 11, 12}， $k = 1$。  
    $k = 1$，比較 $index = \frac{1}{2} -1 = 0$ 的數， $nums1[0] = nums2[0] = 8$，此時刪除哪一方的都可以，因此刪除 `nums1[0]` 和其左邊的數，`k` 的值減去刪除的數的數量， $k = 1 - 1 = 0$。當 `k` 的值為 0 時，代表已經找到第 `k` 小的數，也就是 `nums2[0]`。  

如果某一個 array 的長度小於 $\frac{k}{2}$ 時，可以直接比較該 array 的最後一個數和另一個 array 的第 $\frac{k}{2}$ 個數，像是以下例子:

1. `nums1` = {1, 2}，`nums2` = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}， $k = \frac{2+10}{2} = 6$。  
    比較 $index = \frac{6}{2} -1 = 2$ 的數，由於 `nums1` 長度不足因此直接比較 `nums1` 的最後一個數， $nums1[1] = 2 < nums2[2] = 3$，因此刪除 `nums1[1]` 和其左邊的數，`k` 的值減去刪除的數的數量， $k = 6 - 2 = 4$。  
2. `nums1` = {}，`nums2` = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}， $k = 4$。  
    此時 `nums1` 已經沒有數字了，因此第 `k` 小的數就是 $nums2[k-1] = nums2[3] = 4$。

在計算中位數時，如果 $m+n$ 為奇數，則中位數為第 $\frac{m+n+1}{2}$ 小的數，如果 $m+n$ 為偶數，則中位數為第 $\frac{m+n+1}{2}$ 小的數和第 $\frac{m+n+2}{2}$ 小的數的平均值。

##### 程式碼

```c++ {.line-numbers}
class Solution {
  public:
    int findKthNumber(std::vector<int> &nums1, std::vector<int> &nums2, int k) {
        int n = nums1.size(), m = nums2.size();
        int n_index = 0, m_index = 0; // 紀錄兩個 array 當前的起始 index

        while (true) {
            // nums1 的值都小於中位數，中位數等於 nums2[m_index + (k - 1)]
            if (n_index >= n) {
                return nums2[m_index + (k - 1)];
            }
            // nums2 的值都小於中位數，中位數等於 nums1[n_index + (k - 1)]
            if (m_index >= m) {
                return nums1[n_index + (k - 1)];
            }

            // k = 1 時表示要找第一小的數，可以直接比較
            if (k == 1) {
                return std::min(nums1[n_index], nums2[m_index]);
            }

            // 取得兩個 array 當前第 k/2 的數 的 index，若 index 超出範圍則取最後一個數
            int n1_cur = (n - n_index >= k / 2) ? n_index + k / 2 - 1 : n - 1;
            int n2_cur = (m - m_index >= k / 2) ? m_index + k / 2 - 1 : m - 1;

            // 比較兩個數的大小
            // 中位數不在 nums2[m_index] 到 nums2[cur] 之間，將其排除搜索範圍
            if (nums1[n1_cur] > nums2[n2_cur]) {
                k -= (n2_cur - m_index + 1); // 這行要先做，因為 m_index 在下行會改動
                m_index = n2_cur + 1;
            }
            // 中位數不在 nums1[n_index] 到 nums1[cur] 之間，將其排除搜索範圍
            else {
                k -= (n1_cur - n_index + 1); // 這行要先做，因為 n_index 在下行會改動
                n_index = n1_cur + 1;
            }
        }

        return -1; // 不會執行到這行
    }
    double findMedianSortedArrays(std::vector<int> &nums1, std::vector<int> &nums2) {
        // 算出中位數是第幾個數
        // 如果 n + m 是奇數，像是 3，則median_left 和 median_right 都會是 2
        // 如果 n + m 是偶數，像是 4，則median_left 是 2，median_right 是 3
        // 由於這是第幾個數，是從 1 開始算，因此後續在處理 index 相關的程式碼時要減 1
        int median_left = (nums1.size() + nums2.size() + 1) / 2;
        int median_right = (nums1.size() + nums2.size() + 2) / 2;

        return (findKthNumber(nums1, nums2, median_left) + findKthNumber(nums1, nums2, median_right)) / 2.0;
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241207224855419.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241207224855419.png)

時間複雜度: $O(log(m+n))$  
空間複雜度: $O(1)$

#### 方法 2

對於一個 `nums` = {n1, n2, ... , nk} 來說，如果要將其分成兩半，有共 $k+1種$ 分法，像是以下例子:  
`nums` = {1, 2, 3, 4}，以`|` 來進行分隔的話會變成 | 1 | 2 | 3 | 4 |，可以任選一個 `|` 將 `nums` 分成兩半，在這個例子中共有 5 個 `|`，因此有 5 種辦法能分兩半。  

對於 `nums1` = {a1, a2, ... , an}、`nums2` = {b1, b2, ... , bm}，令 `i` 為分割 `nums1` 的位置，`j` 為分割 `nums2` 的位置，則 `nums1` 在 `i` 左邊的數字共有 `i` 個，`nums2` 在 `j` 左邊的數字共有 `j` 個。

```text
此圖為示意圖，並非實際分割點位置， i 並不一定等於 j!

                              |-> 分割點 i
`nums1` =   |a1|a2|a3| ... |ai|ai+1| ... |an|
`nums2` =   |b1|b2|b3| ... |bj|bj+1| ... |bm|
                              |-> 分割點 j
```

將 `i` 和 `j` 的左邊合稱為**左半部分**，`i` 和 `j` 的右邊合稱為**右半部分**。  

- 當 `nums1` 和 `nums2` 的長度總和為偶數時，如果能滿足以下條件:

  - 左半部分的數量等於右半部分的數量，也就是 $i + j = n + m - i - j$，則 $j = \frac{n + m}{2} - i$ 。  
  - 左半部分的最大值小於等於右半部分的最小值，也就是  
    $$max(nums1[i-1], nums2[j-1]) \leq min(nums1[i], nums2[j])$$  

  那麼中位數就會是左半部分的最大值和右半部分的最小值的平均值，也就是  

  $$\frac{max(nums1[i-1], nums2[j-1]) + min(nums1[i], nums2[j])}{2}$$

- 當 `nums1` 和 `nums2` 的長度總和為奇數時，如果能滿足以下條件:

  - 左半部分的數量比右半部分的數量多 1，也就是 $i + j = n + m - i - j + 1$，則 $j = \frac{n + m + 1}{2} - i$ 。  
  - 左半部分的最大值小於等於右半部分的最小值，也就是  
    $$max(nums1[i-1], nums2[j-1]) \leq min(nums1[i], nums2[j])$$

  那麼中位數就會是左半部分的最大值，也就是  
  $$max(nums1[i-1], nums2[j-1])$$

上述條件中的第一個條件， $n+m$為偶數時 $j = \frac{n + m}{2} - i$ 和 $n+m$ 為奇數時 $j = \frac{n + m + 1}{2} - i$，因為是整數除法運算，對於偶數先 +1 再除以 2 的結果是一樣的，所以可以統和成 $j = \frac{n + m + 1}{2} - i$。  
而 `i` 的範圍是 $0 \leq i \leq n$、`j` 的範圍是 $0 \leq j \leq m$，根據 $j = \frac{n + m + 1}{2} - i$ 來看，為了避免 `j` 超過範圍，所以必須要保證 $m \geq n$ 。  

而第二個條件 $max(nums1[i-1], nums2[j-1]) \leq min(nums1[i], nums2[j])$ 對於偶數和奇數都是一樣的，由於 `nums1` 和 `nums2` 都是有序的，因此對於這個條件來說 $nums1[i-1] \leq nums1[i]$ 和 $nums2[j-1] \leq nums2[j]$ 是一定成立的，只要保證 $nums1[i-1] \leq nums2[j]$ 且 $nums2[j-1] \leq nums1[i]$ 就能滿足這個條件。  

綜合上述條件，可以得到以下結論:

- 當 $nums2[j-1] > nums1[i]$， $i \neq n$ and $j \neq 0$（避免超出範圍）  
  `nums1` = {2, 4, 6, |i|, 8, 10, 12, 14}，`i` = 3  
  `nums2` = {1, 5, 8, 10, |j|, 11, 12, 12, 15}，`j` = 4  
  這個時候需要將 `i` 往右移，也就是 `i` 要變大，而為了平衡左右部分的數字數量，`j` 也要跟著變小，不過根據 $j = \frac{n + m + 1}{2} - i$，當 `i` 變大時，`j` 自然也會變小，所以不需要額外處理 `j`。  
- 當 $nums1[i-1] > nums2[j]$， $i \neq 0$ and $j \neq m$（避免超出範圍）  
  `nums1` = {2, 4, 13, |i|, 14, 15, 16, 17}，`i` = 3  
  `nums2` = {1, 5, 8, 10, |j|, 11, 12, 12, 15}，`j` = 4  
  這個時候需要將 `i` 往左移，也就是 `i` 要變小，而為了平衡左右部分的數字數量，`j` 也要跟著變大，不過根據 $j = \frac{n + m + 1}{2} - i$，當 `i` 變小時，`j` 自然也會變大，所以不需要額外處理 `j`。  
- 當 $i = 0$ 或 $j = 0$  
  `nums1` = {|i|, a1, a2, ... , an}，`i` = 0  
  `nums2` = {b1, b2, ..., |j|, ... , bm}，`j` = $\frac{n + m + 1}{2} - 0$  
  當 `nums1` 或 `nums2` 的**左半部分為空**，這時候**左半部分的最大值**會是 `nums2[j-1]` 或 `nums1[i-1]`，右半部分的最小值仍是 $min(nums1[i], nums2[j])$ 。  
- 當 $i = n$ 或 $j = m$
  `nums1` = {a1, a2, ... , an, |i|}，`i` = n  
  `nums2` = {b1, b2, ..., |j|, ... , bm}，`j` = $\frac{n + m + 1}{2} - n$  
  當 `nums1` 或 `nums2` 的**右半部分為空**，這時候**右半部分的最小值**會是 `nums2[j]` 或 `nums1[i]`，左半部分的最大值仍是 $max(nums1[i-1], nums2[j-1])$ 。

整理好所有條件後，接著要初始化 `i` 和 `j`，可以將 `i` 初始化為  `nums1` 的中間值，也就是 $i = \frac{n}{2}$，然後根據 $j = \frac{n + m + 1}{2} - i$ 來計算 `j` 的值，而 `i` 和 `j` 的範圍是 $0 \leq i \leq n$、$0 \leq j \leq m$ 。  
初始化 $l = 0$ 、 $r = n$，用 binary search 來搜索整個 `nums1`，範圍為 $[l,r]$， $i = \frac{l + r}{2}$ 、 $j = \frac{n + m + 1}{2} - i$，然後根據 $nums1[i-1] \leq nums2[j]$ 和 $nums2[j-1] \leq nums1[i]$ 來判斷是否滿足條件，如果滿足條件，則找到中位數，如果沒有滿足條件，則根據 $nums1[i-1] > nums2[j]$ 或 $nums2[j-1] > nums1[i]$ 來調整 `i` 和 `j` 的值，直到滿足條件為止。  

##### 程式碼

```c++
class Solution {
  public:
    double findMedianSortedArrays(std::vector<int> &nums1, std::vector<int> &nums2) {
        int n = nums1.size(), m = nums2.size();

        // 讓較小的array始終為 nums1
        if (n > m) {
            return findMedianSortedArrays(nums2, nums1);
        }

        // 用 binary search 搜索整個 nums1，範圍為 [0, n]，並且 nums1 的分割點 就是這個搜索範圍的平均值
        int nums1_left = 0, nums1_right = n;

        while (nums1_left <= nums1_right) {
            int mid1 = (nums1_left + nums1_right) / 2; // nums1 的分割點
            int mid2 = (n + m + 1) / 2 - mid1;         // nums2 的分割點
            int l1 = INT_MIN, l2 = INT_MIN;            // l1 和 l2 各為 nums1 和 nums2 左邊部分的最大值
            int r1 = INT_MAX, r2 = INT_MAX;            // r1 和 r2 各為 nums1 和 nums2 右邊部分的最小值

            // 設定l1, l2, r1, r2的值，if 中的判斷均為邊界條件的判斷，避免 index 超出範圍
            if (mid1 > 0) {
                l1 = nums1[mid1 - 1];
            }
            if (mid2 > 0) {
                l2 = nums2[mid2 - 1];
            }
            if (mid1 < n) {
                r1 = nums1[mid1];
            }
            if (mid2 < m) {
                r2 = nums2[mid2];
            }

            // 如果l1 > r2，表示 nums1 左邊部分太大，需要將 nums1 左邊部分縮小，反之則將 nums1 左邊部分增加
            if (l1 > r2) {
                nums1_right = mid1 - 1;
            }
            else if (l2 > r1) {
                nums1_left = mid1 + 1;
            }
            // 如果 l1 <= r2 && l2 <= r1，所有條件都符合了，找到答案
            else {
                // 判斷總長度為奇數或偶數，奇數時回傳左半部分最大值，偶數時回傳左半部分最大值和右半部分最小值的平均值
                if ((n + m) % 2 == 1) {
                    return static_cast<double>(std::max(l1, l2));
                }
                else {
                    return static_cast<double>(std::max(l1, l2) + std::min(r1, r2)) / 2.0;
                }
            }
        }

        // 如果沒有找到答案，回傳 -1
        return -1;
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241208102053419.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241208102053419.png)

時間複雜度: $O(log(min(m, n)))$  
空間複雜度: $O(1)$

[參考資料](https://leetcode.wang/leetCode-4-Median-of-Two-Sorted-Arrays.html)
