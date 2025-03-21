# <center> [2440. Create Components With Same Value](https://leetcode.com/problems/create-components-with-same-value/description/) </center>

## 題目敘述

[![](https://i.imgur.com/pJPtyn2.png)](https://i.imgur.com/pJPtyn2.png)

給一個有 `n` 個節點的 **無向多叉樹（Undirected Multiway Tree）**，節點編號為 `0` 到 `n-1`，以及一個一維整數陣列 `nums` 和二維整數陣列 `edges`，`nums[i]` 代表節點 `i` 的值， $edge[i] = [u, v]$ 代表節點 `u` 和節點 `v` 互相連通，可以對任意相連的節點進行切割，切割後的每個子樹的總和相同，求最多可以切割出幾個子樹。

- 題目保證 `edges` 是無向樹

## 解題思路

### 1. DFS

這道題目和 [2872. Maximum Number of K-Divisible Components](https://leetcode.com/problems/maximum-number-of-k-divisible-components/description/) 類似，都是樹形 DP 的題目，寫法幾乎一樣，這邊只討論不同的地方。

題目要求切割後的每個子樹的總和相同，`n` 個節點會有 `n` 種切割方法，首先算出 tree 的總和 `sum`，然後嘗試每一種方法，如果 `sum` 可以被 `n` 整除，表示該方法是有機會成功的，因此以 $k = \frac{sum}{n}$ 為每個子樹的總和目標，然後用 DFS 計算每個節點的子樹總和，如果子樹總和為 `k` 就代表該子樹可以被切割，只要有任何一個子樹總和超過 `k` 就代表該方法無法成功，繼續嘗試下一種方法。

#### 程式碼

```cpp {.line-numbers}
// 將 adj 鄰接圖表創建為全域變數，這樣可以提高效能和降低記憶體使用率
// 如果是在 class 內創建，每次呼叫 maxKDivisibleComponents() 都得重新分配和釋放記憶體
const int N = 2e4 + 5;
std::vector<std::vector<int>> adj(N);

class Solution {
  public:
    int dfs(int pre_node, int curr_node, const std::vector<int> &values, const int &k) {
        // 計算當前節點的子樹總和
        int sum = values[curr_node];
        for (auto &next_node : adj[curr_node]) {
            if (next_node != pre_node) {
                sum += dfs(curr_node, next_node, values, k);
            }
        }

        // 如果當前節點的子樹總和等於 k，該子樹可以被分割，返回上一層繼續檢查其他子樹
        if (sum == k) {
            return 0;
        }
        return sum;
    }

    int componentValue(std::vector<int> &nums, std::vector<std::vector<int>> &edges) {
        // 清空 adj 鄰接圖表，避免之前的測試資料影響當前測試資料的結果
        int sum = 0, n = nums.size();
        for (int i = 0; i < nums.size(); ++i) {
            adj[i].clear();
            sum += nums[i];
        }

        // 創建鄰接圖表
        for (auto &edge : edges) {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }

        // tree 可以被分成 [1, n] 個子數，且題目要求"最多"的子樹，所以從 n 開始遍歷到 1
        // 因為是從最多子樹的方法開始遍歷，一旦找到一個可以均分的方法，該方法必為分割最多子樹的方法，可以直接跳出迴圈
        for (int i = n; i > 0; --i) {
            // 整個樹的總和必須可以被 i 整除，否則無法均分
            if (sum % i != 0) {
                continue;
            }

            // 若 dfs 返回 0，表示可以將子樹分割成 i 個子樹，且每個子樹的值總和相等
            // 題目求可以分割幾次，return i - 1
            if (dfs(-1, 0, nums, sum / i) == 0) {
                return i - 1;
            }
        }

        return -1;
    }
};
```

[![](https://i.imgur.com/PX09UJ5.png)](https://i.imgur.com/PX09UJ5.png)

#### 複雜度分析

令 $n$ 為節點的數量，`sum` 為樹的總和，$f(sum)$ 為 `sum` 的因數數量。

- 時間複雜度： $O(n \cdot f(sum))$

- 空間複雜度： $O(n)$
