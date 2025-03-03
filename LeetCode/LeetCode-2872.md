# <center> [2872. Maximum Number of K-Divisible Components](https://leetcode.com/problems/maximum-number-of-k-divisible-components/description/) </center>

## 題目敘述

[![](https://i.imgur.com/dkbbdKi.png)](https://i.imgur.com/dkbbdKi.png)

給一個有 `n` 個節點的 **無向多叉樹 （Undirected Multiway Tree）**，節點編號為 $0$ 到 $n - 1$ ，以及一維整數陣列 `values`、二維整數陣列 `edges`、除數 `k`，`values[i]` 代表 `node i` 的值， $edge[i] = [u, v]$ 代表節點 `u` 和 `v` 連通。

可以對任意相連的節點進行切割，切割後的每個子樹的總和必須可以被 `k` 給整除，求最多可以切割出幾個子樹。

- 保證 `values` 的合可以被 `k` 整除

- 保證 `edges` 是無向樹

e.g.

1. $n = 5$ ， $edges = [[0, 2], [1, 2], [1, 3], [2, 4]]$ ， $values = [1, 8, 1, 4, 4]$ ， $k = 6$

    [![](https://i.imgur.com/DhYD0Dn.png)](https://i.imgur.com/DhYD0Dn.png)

    最多可以將 `node 1` 和 `node 2` 進行切割，切割後的子樹總和分別為 6 和 12，都可以被 6 整除，子樹共 2 個所以答案為 2。

2. $n = 7$ ， $edges = [[0, 1], [0, 2], [1, 3], [1, 4], [2, 5], [2, 6]]$ ， $values = [3, 0, 6, 1, 5, 2, 1]$ ， $k = 3$

    [![](https://i.imgur.com/iPLLrf4.png)](https://i.imgur.com/iPLLrf4.png)

    最多可以將 `node 0` 和 `node 1` 以及 `node 0` 和 `node 2` 切割，切割後的子樹總和分別為 0、6、9，都可以被 3 整除，子樹共 3 個所以答案為 3。

## 解題思路

### 1. DFS

這題其實就是一個樹形 DP 的題目，題目保證整棵樹的總合 `treeSum` 可以被 `k` 整除，可以透過 DFS 來計算每個節點的子樹總和，分為兩種情況：

1. 當前節點的子樹總和可以被 `k` 整除：如果將該子樹分割，那麼整棵樹的總合就會變成 $treeSum - subTreeSum$ ，因為`treeSum` 原本就可以被 `k` 整除，就算切割了這個子樹，`treeSum` 還是可以被 `k` 整除，因此可以將該子樹進行切割。

2. 當前節點的子樹總和不可以被 `k` 整除：如果將該子樹分割，那麼整棵樹的總合就會變成 $treeSum - subTreeSum$ ，此時 `treeSum` 就無法被 `k` 整除，而且 `subTreeSum` 也無法被 `k` 整除，因此不能將該子樹進行切割。

由於這是一個無向樹，因此可以選任何一個節點當 `root`，這邊選擇 `node 0` 作為 `root`，因為整個 tree 可能只有一個節點，以 `node 0` 作為 `root` 可以保證這個 `root` 一定存在。

實際例子操作如下：

$n = 5$ ， $edges = [[0, 2], [1, 2], [1, 3], [2, 4]]$ ， $values = [1, 8, 1, 4, 4]$ ， $k = 6$

[![](https://i.imgur.com/6BwI54s.png)](https://i.imgur.com/6BwI54s.png)

由於是以 `node 0` 為 `root`，因此樹實際上會以這樣來處理：

[![](https://i.imgur.com/Tggio7c.png)](https://i.imgur.com/Tggio7c.png)

用 DFS 計算每個節點的子樹總和：

[![](https://i.imgur.com/280D6h1.png)](https://i.imgur.com/280D6h1.png)

可以看到 `node 1` 的子樹總合是 12 能被 `k` 整除，因此將其切割。

[![](https://i.imgur.com/TXOnKN7.png)](https://i.imgur.com/TXOnKN7.png)

剩餘的節點子樹總和只有 `root` 可以 `k` 整除，因此共可以分成 2 個子樹，答案為 2。

#### 程式碼

```cpp {.line-numbers}
// 將 adj 鄰接圖表創建為全域變數，這樣可以提高效能和降低記憶體使用率
// 如果是在 class 內創建，每次呼叫 maxKDivisibleComponents() 都得重新分配和釋放記憶體
const int N = 3e4 + 5;
std::vector<std::vector<int>> adj(N);

class Solution {
  public:
    int res = 0;

    long long dfs(int pre_node, int curr_node, const std::vector<int> &values, const int &k) {
        long long sum = values[curr_node];
        // 計算當前節點的子樹總和
        for (auto &next_node : adj[curr_node]) {
            if (next_node != pre_node) {
                sum += dfs(curr_node, next_node, values, k);
            }
        }

        // 如果當前子樹總和能被 k 整除，則該子樹能和 perent node 分開形成獨立的 component
        sum %= k;
        res += sum == 0;
        return sum;
    }

    int maxKDivisibleComponents(int n, std::vector<std::vector<int>> &edges, std::vector<int> &values, int k) {
        // 清空 adj 鄰接圖表，避免之前的測試資料影響當前測試資料的結果
        for (int i = 0; i < n; ++i) {
            adj[i].clear();
        }
        // 創建鄰接圖表
        for (auto &edge : edges) {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }

        dfs(-1, 0, values, k);

        return res;
    }
};
```

[![](https://i.imgur.com/NEqk3cx.png)](https://i.imgur.com/NEqk3cx.png)

#### 複雜度分析

令 $n$ 為節點的數量。

- 時間複雜度： $O(n)$

- 空間複雜度： $O(n)$

    `adj` 鄰接圖表的空間複雜度為 $O(n)$ ，`dfs` 遞迴深度最糟為 $O(n)$ 。
