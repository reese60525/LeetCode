# <center> [1319. Number of Operations to Make Network Connected](https://leetcode.com/problems/number-of-operations-to-make-network-connected/description/) </center>

## 題目敘述

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures202412312134148.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures202412312134148.png)

給一個整數 `n` 表示有共有 `n` 台電腦，和一個整數陣列 `connections`，其中 `connections[i] = {ai, bi}` 表示電腦 `ai` 和 `bi` 之間有一條線連接。對於每個連接的電腦，可以將連接線拿走並拿給別的電腦使其連接，請問最少需要幾次操作才能讓所有電腦連接在一起，如果無法連接所有電腦，則回傳 -1。

## 解題思路

假設有以下輸入：

`n` = 12，`connections` = {{0, 1}, {0, 2}, {0, 3}, {4, 5}, {4, 6}, {4, 7}, {5, 7}, {6, 7}, {8, 9}, {10, 2}, {10, 3}}

將圖畫出來：

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures202412312139758.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures202412312139758.png)

可以發現要將所有電腦連接在一起，需要將整張圖變成一個連通圖，圖中共有 4 個連通分量，所以最少需要 3 條線 3 次操作才能將所有電腦連接在一起。

### 1. DFS

首先可以先確認連接線的數量 `m` 是否能夠連接所有電腦，有 `n` 台電腦就需要至少 `n-1` 條線，如果 $m < n - 1$ 表示無法連接所有電腦，直接回傳 -1。

接著用 DFS 將每台電腦當作 `root` 來遍歷，並將走訪過的節點標記為 visited，如果當前 `root` 沒有被遍歷過，表示這個 `root` 是一個新的連通分量，計算出所有連通分量的數量 `k` 之後，需要 `k - 1` 條線才能將所有電腦連接在一起。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    int makeConnected(int n, std::vector<std::vector<int>> &connections) {
        // 判斷連接線的數量是否足夠連接所有電腦
        if (connections.size() < n - 1) {
            return -1;
        }

        // 建立鄰接表
        std::vector<bool> visited(n, false);
        std::vector<std::vector<int>> adj(n);
        for (auto &v : connections) {
            adj[v[0]].push_back(v[1]);
            adj[v[1]].push_back(v[0]);
        }

        // DFS 走訪所有節點
        auto dfs = [&](auto &&dfs, int cur) {
            if (visited[cur]) {
                return;
            }

            visited[cur] = true;
            for (int next : adj[cur]) {
                if (!visited[next]) {
                    dfs(dfs, next);
                }
            }
        };

        int res = 0;
        for (int i = 0; i < n; ++i) {
            // 若當前節點未被走訪過，表示這是一個新的連通分量
            res += !visited[i];
            dfs(dfs, i);
        }

        // 需要連接的線數為連通分量數量 - 1
        return res - 1;
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures202412312200214.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures202412312200214.png)

#### 複雜度分析

令 $n$ 是電腦的數量， $m$ 是連接線的數量。

- 時間複雜度： $O(n + m)$

- 空間複雜度： $O(n + m)$

### 2. Union Find

可以將有相同 `root` 的節點視為同一個連通分量，並用 Union Find 來計算連通分量的數量。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    int makeConnected(int n, std::vector<std::vector<int>> &connections) {
        // 判斷連接線的數量是否足夠連接所有電腦
        if (connections.size() < n - 1) {
            return -1;
        }

        // parent 紀錄每個節點的父親， rank 紀錄每個 root 的高度（深度）
        int parent[n], rank[n];
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
            rank[i] = 1;
        }

        // 找 root 以及路徑壓縮
        auto find = [&](auto &&find, int x) -> int {
            return x == parent[x] ? x : parent[x] = find(find, parent[x]);
        };

        // 對每個邊進行處理
        for (auto &v : connections) {
            int root_x = find(find, v[0]);
            int root_y = find(find, v[1]);

            // 按照 rank 來合併，樹高較矮的合併到樹高較高的
            if (rank[root_x] > rank[root_y]) {
                std::swap(root_x, root_y);
            }
            parent[root_x] = root_y;
            // 如果兩個樹的 rank 一樣，則合併後的樹高需要 + 1
            rank[root_y] += rank[root_x] == rank[root_y];
        }

        // 計算不同連通分量的數量
        int res = 0;
        for (int i = 0; i < n; ++i) {
            res += parent[i] == i;
        }

        // 需要連接的線數為連通分量數量 - 1
        return res - 1;
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures202412312358207.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/Pictures202412312358207.png)

#### 複雜度分析

令 $n$ 是電腦的數量， $m$ 是連接線的數量， $\alpha(n)$ 是反阿克曼函數，是一個增長非常緩慢的函數，可以視為常數。

- 時間複雜度： $O(m + \alpha(n))$

- 空間複雜度： $O(n)$ 。
