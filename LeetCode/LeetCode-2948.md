# <center> [2948. Make Lexicographically Smallest Array by Swapping Elements](https://leetcode.com/problems/make-lexicographically-smallest-array-by-swapping-elements/description/) </center>

## 題目敘述

![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures202501271853782.png)

給一個整數陣列 `nums` 和整數 `limit`，對於 `nums[i]` 和 `nums[j]`，如果 $i \neq j \text{ and } abs(nums[i] - nums[j]) \leq limit$ ，則 `nums[i]` 可以和 `nums[j]` 進行交換操作。

請找出將 `nums` 陣列進行交換操作後所能得到的**最小字典序**結果。

假如 $nums = [22, 21, 111, 9]$ ，則**最小字典序**為 `[9, 21, 22, 111]`。

## 解題思路

### 1. Sorting

假如有 $nums = [1, 4, 9]$ 以及 $limit = 5$ ，1 和 4 以及 4 和 9 都可以進行交換操作，那麼1 和 9 可以交換嗎？答案是可以的，如下所示：

- 將 1 和 4 交換： $nums = [4, 1, 9]$ 。

- 將 4 和 9 交換： $nums = [9, 1, 4]$ 。

- 將 1 和 4 交換： $nums = [9, 4, 1]$ 。

可以發現這之間是有鏈結關係的，若 `a` 可以和 `b` 交換且 `b` 可以和 `c` 交換，則 `a` 可以和 `c` 交換，可以一直無限擴展。

因此可以將 `nums` 中所有整數進行分組，只要是同一組的整數就能任意交換。將 `nums` 進行排序，檢查 `nums[i]` 和 `nums[i-1]`：

- $nums[i] - nums[i-1] \leq limit$ ：可以交換，屬於同一個組別。

- $nums[i] - nums[i-1] > limit$ ：無法交換，`nums[i]` 是一個新的組別。

將所有 `nums` 中的整數分好組別之後，遍歷 `nums`，依序填入每個組別由小到大的整數即可得到答案。

演算法流程：

1. 創建 `groupId` 表示組別編號，`sortedNums` 陣列儲放排序後的 `nums` 的 value 和 index，`groupsIndex` 則是每個組別在 `sortedNums` 中的起始 index。

    > 將所有整數分好組別後，`groupsIndex` 用於將每個組別的整數由小到大填入至要 return 的答案中。  
    以 $nums = [8, 5, 2 ,14, 55, 33, 16] \text{、}limit = 4$ 為例：  
    將 `nums` 排序後會變成 `[2, 5, 8 ,14, 16, 33, 55]`，能分組成：`[[2, 5, 8], [14, 16], [33], [55]]`，而 `groupsIndex` 會記錄 `nums` 排序後每一組的起始 index， $groupsIndex = [0, 3, 5, 6]$ ，這麼一來後續在填入答案時，假使當前 `nums[i]` 是 group 0、 $groupsIndex[0] = 0$ ，則 `nums[i]` 會填入 $sortedNums[groupsIndex[0]] = sortedNums[0]$ 也就是 group 0 最小的整數，然後將 $groupsIndex[0] + 1$ ，下次再遇到 group 0 就會把該組第二小的整數填入，以此來完成**最小字典序**。

2. 遍歷 `nums`，檢查 `nums[i]` 和 `nums[i-1]` 是否可以交換，如果不能就將 $groupId + 1$ 表示新組別。接著更新 `nums[i] = groupId` 用來紀錄 `nums[i]` 的組別。

3. 遍歷 `nums`，根據組別依序將該組別當前未使用的最小的整數填入。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    std::vector<int> lexicographicallySmallestArray(std::vector<int> &nums, int limit) {
        int n = nums.size(), groupId = 0;
        std::vector<int> groupsIndex {0}; // 紀錄每個組別在排序後的起始 index
        std::vector<std::pair<int, int>> sortedNums(n);

        // 將 nums 的 value、index 綁定並排序
        for (int i = 0; i < n; ++i) {
            sortedNums[i] = {nums[i], i};
        }
        std::sort(sortedNums.begin(), sortedNums.end(),
                  [&](const std::pair<int, int> &a, const std::pair<int, int> &b) {
                      return a.first < b.first;
                  });

        // 將 nums 所有 element 進行分組，並將分組的結果存入 nums 中
        // 例如：nums[i] = k 表示該位置的整數屬於 group k
        int cur, pre;
        nums[sortedNums[0].second] = groupId;
        for (int i = 1; i < n; ++i) {
            cur = sortedNums[i].first;
            pre = sortedNums[i - 1].first;
            // 若無法交換則新增一個 group，並將在 sortedNums 中的起始 index 存入 groupsIndex 中
            if (cur - pre > limit) {
                ++groupId;
                groupsIndex.push_back(i);
            }
            // 紀錄 nums 當前位置的組別
            nums[sortedNums[i].second] = groupId;
        }

        // 遍歷 nums，根據組別依序將該組的整數由小到大填入
        for (int &num : nums) {
            num = sortedNums[groupsIndex[num]++].first;
        }

        return nums;
    }
};
```

![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures202501271936805.png)

#### 複雜度分析

令 $n$ 為 `nums` 的長度。

- 時間複雜度： $O(n \log n)$

    排序需要 $O(n \log n)$ ，其他操作都是 $O(n)$ 。

- 空間複雜度： $O(n)$
