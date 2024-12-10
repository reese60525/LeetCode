# <center> [LeetCode - 3152. Special Array II](https://leetcode.com/problems/special-array-ii/description/https://leetcode.com/problems/special-array-ii/description/) </center>

## 題目敘述

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241210161408270.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241210161408270.png)

給一個 integer array `nums` 和一個 2D integer array `queries`，`queries[i] = {start, end}`，`start` 和 `end` 代表 `nums` 的 subarray 的起始 `index` 和結尾 `index`。如果 `queries[i]` 這範圍所形成的 subarray 是 `special array`，則回傳 `true`，否則回傳 `false`。  

special array 的定義為：  

- 每個相鄰的數字都必須為不同的奇偶性。  

e.g. `nums` = {1,2,3,4,5,7,6,8}  

- {1, 2, 3} 是 `special array`，因為相鄰兩數的奇偶性都**不同**。  
- {4, 5, 7} 不是 `special array`，因為 5 和 7 的奇偶性**相同**。  
- {6, 8} 不是 `special array`，因為 6 和 8 的奇偶性**相同**。  

## 解題思路

### 1. Prefix Sum

遍歷 `nums` 進行 `special array` 分組，組別從第 0 組開始，如果 `nums[i]` 和 `nums[i-1]` 的奇偶性相同，代表 `nums[i]` 和 `nums[i-1]` 屬於不同的組別，所以 `nums[i]` 的組別為 `nums[i-1]` 的組別 + 1。  

e.g.

`nums` = {1,4,5,7,6,8}  

- 一開始的組別為 0，所以 `nums[0]` 的組別為 0。
- `nums[1]` 和 `nums[0]` 的奇偶性**不同**，所以 `nums[1]` 的組別等於 `nums[0]`，`nums[1]` 的組別為 0。
- `nums[2]` 和 `nums[1]` 的奇偶性**不同**，所以 `nums[2]` 的組別等於 `nums[1]`，`nums[2]` 的組別為 0。
- `nums[3]` 和 `nums[2]` 的奇偶性**相同**，所以 `nums[3]` 的組別等於 `nums[2]` + 1，`nums[3]` 的組別為 1。
- `nums[4]` 和 `nums[3]` 的奇偶性**不同**，所以 `nums[4]` 的組別等於 `nums[3]`，`nums[4]` 的組別為 1。
- `nums[5]` 和 `nums[4]` 的奇偶性**相同**，所以 `nums[5]` 的組別等於 `nums[4]` + 1，`nums[5]` 的組別為 2。

最後，我們可以得到 `nums` 的組別為 {0, 0, 0, 1, 1, 2}。由這組數據可以得知如果 `nums[i]` 和 `nums[j]` 的組別相同，代表 $index = [nums[i],nums[j]]$ 所形成的 subarray 是 `special array`。

#### 程式碼

```c++ {.line-numbers}
class Solution {
  public:
    std::vector<bool> isArraySpecial(std::vector<int> &nums, std::vector<std::vector<int>> &queries) {
        int n = nums.size(), k = 0; // k 表示當前共有幾組 special subarray
        int prev = ~(nums[0] & 1); // prev 表示前一個數字是奇數還是偶數，初始化為 nums[0] 的奇偶數的相反

        // 遍歷 nums 計算每個數字目前遇到的 special subarray 數量，並將結果存儲在 nums 中
        for (int &num : nums) {
            k += prev == (num & 1); // 如果當前數字和前一個數字奇偶性相同，則 k 加 1
            prev = num & 1;         // 更新 prev 為當前數字的奇偶性
            num = k;                // 將 num 設為count，表示該數是屬於第 k 組的 special subarray
        }

        // 查詢兩個數之間的 subarray 是否為 special subarray
        // 若兩數都屬於同一組則這兩數能形成 special subarray
        int i = 0;
        std::vector<bool> res(queries.size());
        for (std::vector<int> &query : queries) {
            res[i++] = nums[query[0]] == nums[query[1]];
        }

        return res;
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241209144541582.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures/20241209144541582.png)

時間複雜度： $O(n+q)$ ，其中 $n$ 是 `nums` 的長度， $q$ 是 `queries` 的長度。  
空間複雜度： $O(1)$ ，return 的空間不算在內，我們只對 `nums` 進行了原地修改，所以空間複雜度為 $O(1)$ 。
