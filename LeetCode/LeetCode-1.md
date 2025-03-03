# <center> [1. Two Sum](https://leetcode.com/problems/two-sum/description/) </center>

## 題目敘述

[![](https://i.imgur.com/BKK8m1E.png)](https://i.imgur.com/BKK8m1E.png)

給一組不重複的整數陣列 `nums` 和一個整數 `target`，找出能一對不相同的 `[num[i], num[j]]` 使 $nums[i] + num[j] = target$ ，並return `[i, j]`。

**題目保證洽有一個解**

## 解題思路

### 1. Hash Map

建立 hash map，遍歷 `nums` 將 `[nums[i], i]` 存入，同時檢查 $target - nums[i]$ 是否存在於 hash map 中，若存在則 return `[i, hash[target - nums[i]]]`。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    std::vector<int> twoSum(std::vector<int> &nums, int target) {
        std::unordered_map<int, int> table; // {value, index}

        for (int i = 0; i < nums.size(); ++i) {
            // 查找另一個數是否存在於 table 中
            if (table.find(target - nums[i]) != table.end()) {
                return {i, table[target - nums[i]]};
            }

            table[nums[i]] = i; // 將 nums[i] 的 index 存入 table 中
        }

        // 因為必定洽有一組解，所以這行不會用到，只是為了過編譯
        return {-1, -1};
    }
};
```

[![](https://i.imgur.com/I6skfi1.png)](https://i.imgur.com/I6skfi1.png)

#### 複雜度分析

令 $n$ 為 `nums` 的長度。

- 時間複雜度: $O(n)$

- 空間複雜度: $O(n)$
