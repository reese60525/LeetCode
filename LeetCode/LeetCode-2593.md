# <center> [2593. Find Score of an Array After Marking All Elements](https://leetcode.com/problems/find-score-of-an-array-after-marking-all-elements/description/) </center>

## 題目敘述

[![](https://i.imgur.com/PMaRDG1.png)](https://i.imgur.com/PMaRDG1.png)

給一個長度為 `n` 的正整數陣列 `nums`，每次操作可以選擇 `nums` 中 **未被標記的最小值** `nums[i]`，累加該值並將其 **本身和左右** 的 element 標記，將 `nums` 所有 element 都標記後，求最後的總和。

e.g.

$nums = [2, 1, 3, 4, 5, 2]$

1. 選擇 `nums[1]` 並標記，累加 1，並將 `nums[0]` 和 `nums[2]` 標記。

2. 選擇 `nums[5]` 並標記，累加 2，並將 `nums[4]` 標記。

3. 選擇 `nums[3]` 並標記，累加 4。

最後總和為 $1 + 2 + 4 = 7$

## 解題思路

### 1. Combine Sorting and Hash Map

將 `nums` 由小到大排序，並用一個 bool 陣列紀錄當前已經被標記的 `nums[i]`，接著遍歷排序後的 `nums[i]`，如果 `nums[i]` 沒有被標記則累加 `nums[i]` 並將其排序前的左右 element 標記，最後回傳總和。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    long long findScore(std::vector<int> &nums) {
        // 將 num 和 index 結合
        int n = nums.size();
        std::vector<std::pair<int, int>> binding_idx(n);
        for (int i = 0; i < n; ++i) {
            binding_idx[i] = {nums[i], i};
        }

        // 依照 num 由小到大排序
        std::sort(binding_idx.begin(), binding_idx.end());

        // 遍歷 binding_idx，若該 index 沒被標記，則累加 num 並將 index 和其左右都標記
        long long res = 0;
        bool visited[n];
        std::memset(visited, 0, sizeof(visited));
        for (auto &[num, idx] : binding_idx) {
            if (visited[idx]) {
                continue;
            }

            res += num;
            visited[idx] = true;
            if (idx > 0) {
                visited[idx - 1] = true;
            }
            if (idx < n - 1) {
                visited[idx + 1] = true;
            }
        }

        return res;
    }
};
```

[![](https://i.imgur.com/2ArqFjp.png)](https://i.imgur.com/2ArqFjp.png)

#### 複雜度分析

令 $n$ 為 `nums` 的長度。

- 時間複雜度： $O(n \log n)$

- 空間複雜度： $O(n)$

### 2. Monotonic Stack

因為每次操作都是選擇 **未被標記的最小值**，因此可以將問題轉換成尋找 **找局部最小值** 的問題。

例如： $nums = [2, 1, 3, 4, 5, 2]$ 可以看成 `[[2, 1]、[3]、[4]、[5, 2]]`，在每個遞減區間內，最小的值 `nums[i]` 一定可以選，因為 $nums[i-1] \geq nums[i]$ 且 $nums[i+1] \geq nums[i]$ ，從 `nums[i]` 開始往左 **每隔一個 element**（因為選了 element 後左右都會被標記所以要跳一個 element）遍歷該區間並累加 element，結束區間遍歷後從原本的區間最小值 `nums[i]` **跳一個 element** 往右遍歷 `nums` 繼續找下一個區間，直到遍歷完 `nums`。

這題可以用 stack 來做，但需要許多的 `push` 和 `pop` 操作，效率較差，可以改用 two pointers 來做，概念都是一樣的，只不過是把 stack 的 `push` 和 `pop` 改成 two pointers 的 `++index` 和 `--index` 而已。

e.g.

$nums = [4, 2, 2, 1, 3, 4, 5, 8, 7, 5, 1, 6, 10]$

- 第一個區間為 `[4, 2]`，從 `nums[1]` 開始往左遍歷區間，累加 `nums[1]`，由於左右兩邊會被標記所以跳過 `nums[0]`，結束區間遍歷後從原本的區間最小值 `nums[1]` 往右跳過 `nums[2]`，從 $index = 3$ 繼續找下一個區間，當前總和為 2。

- 第二個區間為 `[1]`，累加該值後從 $index = 5$ 往右找下一個區間，當前總和為 3。

- 第三個區間為 `[4]`，累加該值後從 $index = 7$ 往右找下一個區間，當前總和為 7。

- 第四個區間為 `[8, 7, 5, 1]`，從 `nums[10]` 開始往左遍歷區間，累加 `nums[10]` 並跳過 `nums[9]`，接著累加 `nums[8]` 跳過 `nums[7]`，從 $index = 12$ 繼續找下一個區間，當前總和為 15。

- 第四個區間為 `[10]`，累加該值後從 $index = 14$ 往右找下一個區間，當前總和為 25。

- $index = 14$ 已經遍歷完 `nums`，總和共為 25。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    long long findScore(std::vector<int> &nums) {
        int n = nums.size();
        long long res = 0;

        for (int right = 0; right < n; right += 2) {
            // 當前遞減區間的起始 index
            int left = right;
            // 尋找遞減區間的結尾 index
            while (right < n - 1 && nums[right] > nums[right + 1]) {
                ++right;
            }
            // 往左遍歷區間進行累加
            for (int cur = right; cur >= left; cur -= 2) {
                res += nums[cur];
            }
        }

        return res;
    }
};
```

[![](https://i.imgur.com/505OxtM.png)](https://i.imgur.com/505OxtM.png)

#### 複雜度分析

令 $n$ 為 `nums` 的長度。

- 時間複雜度： $O(n)$

- 空間複雜度： $O(1)$
