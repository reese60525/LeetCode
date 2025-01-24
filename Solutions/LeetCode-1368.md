# <center> [1368. Minimum Cost to Make at Least One Valid Path in a Grid](https://leetcode.com/problems/minimum-cost-to-make-at-least-one-valid-path-in-a-grid/description/) </center>

## 題目敘述

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501181312535.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501181312535.png)

給一個 `m x n` 的二維整數矩陣 `grid` ，其中 `grid[i][j]` 共有 4 種可能的值代表四種方向，表示該位置下一步能夠通往的方向：

- `1`：表示當前位置可向右走。

- `2`：表示當前位置可向左走。

- `3`：表示當前位置可向下走。

- `4`：表示當前位置可向上走。

當順著方向走時，成本為 0，對於每個位置，**最多能修改一次**該位置的方向，並且路徑成本 + 1，請問從 `grid[0][0]` 移動到 `grid[m - 1][n - 1]` 的最小成本為何？

## 解題思路

### 1. Dijkstra's Algorithm

對於這題，將所有 `grid[i][j]` 視為一個點，並且每個點都和其鄰近的點連接（上下左右），而連接的權重為 0 或 1，形成一個有 $m \times n$ 個點和 $4 \times m \times n$ 條邊的有向圖，那使用最短路徑演算法要如何保證每個位置最多只會被修改一次?假設有以下的最短路徑：

$$
P_0, P_1, ..., P_K, P_{K_{11}}, P_{K_{12}}, ..., P_{K_{1X}}, P_K, P_{K_{21}}..., P_{K_{2Y}}
$$

$P_i$ 表示某個位置，該路徑經過 $P_K$ 兩次，因此可以將 $P_K$ 之間的所有位置和任一個 $P_K$ 刪除，得到一條新的路徑：

$$
P_0, P_1, ..., P_K, P_{K_{21}}..., P_{K_{2Y}}
$$

透過這樣的方式，可以將所有出現超過一次的位置刪除，最後所得到的最短路徑每個位置最多只會出現一次，因此**最多只能修改一次**這個條件必定能被滿足。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  private:
    // 右、左、下、上
    static constexpr int dx[4] = {0, 0, 1, -1};
    static constexpr int dy[4] = {1, -1, 0, 0};

    // 將 cost, x, y 打包成一個 int
    inline int pack(int cost, int x, int y) {
        return (cost << 16) | (x << 8) | y;
    }

    // 將 data 解包，轉換成 cost, x, y
    inline std::array<int, 3> unpack(const int &info) {
        return {info >> 16, (info >> 8) & 0xFF, info & 0xFF};
    }

  public:
    int minCost(std::vector<std::vector<int>> &grid) {
        int m = grid.size(), n = grid[0].size();
        // 紀錄已經走過的點
        bool vis[m * n];
        std::memset(vis, false, sizeof(vis));
        // 當前所有能到達的點，成本小的在 heap 頂部，存放的數據是 int（cost 16bit, x 8bit, y 8bit）
        std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
        pq.push({0});

        while (!pq.empty()) {
            std::array<int, 3> info = unpack(pq.top()); // info = {cost, x, y}
            pq.pop();

            // 已經走到終點就回傳答案
            if (info[1] == m - 1 && info[2] == n - 1) {
                return info[0];
            }
            // 走過的點就跳過
            if (vis[info[1] * n + info[2]]) {
                continue;
            }
            vis[info[1] * n + info[2]] = true;

            // 嘗試往四個方向走
            for (int i = 0; i < 4; ++i) {
                int nx = info[1] + dx[i], ny = info[2] + dy[i];
                // 沒有超出範圍且沒走過才能進入 pq
                if (nx >= 0 && nx < m && ny >= 0 && ny < n) {
                    // 計算新的成本，如果要走的方向和現在的方向不同，則成本 + 1
                    int ncost = info[0] + (i + 1 != grid[info[1]][info[2]]);
                    // 將新的點加入 pq
                    pq.emplace(pack(ncost, nx, ny));
                }
            }
        }

        return 0;
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501181600952.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501181600952.png)

#### 複雜度分析

令 $V$ 和 $E$ 分別是有向圖中的節點數和邊數。

- 時間複雜度： $O(m \cdot n \cdot \log(m \cdot n))$

    以 `priority_queue` 來實作 `Dijkstra Algorithm` 時，每個節點最多只會從 `priority_queue` 取出一次，時間複雜度為 $O(V \cdot \log V)$ ，每條邊最多只會被放入 `priority_queue` 一次，時間複雜度為 $O(E \cdot \log V)$ ，因此總時間複雜度為 $O((V + E) \cdot \log V)$ ，在本題中 $V = m \cdot n$ ， $E = 4 \cdot m \cdot n$ ，總時間複雜度為 $O(5 \cdot m \cdot n \cdot \log(m \cdot n)) = O(m \cdot n \cdot \log(m \cdot n))$ 。

- 空間複雜度： $O(m \cdot n)$

    `priority_queue` 和 `vis` 都使用了 $m \cdot n$ 的空間。

---

該解法可以進一步優化時間效率，創建一個 `minCost` 陣列紀錄每個位置的最小成本，只有當前路徑的成本比 `minCost[x][y]` 小時才會將該點加入 `priority_queue` 中，這樣可以減少 `priority_queue` 中的 element 數量，減少插入和移除 element 的時間，而且因為只要成本有變小才會加入 `priority_queue` 中，因此 `vis` 陣列也可以省略。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  private:
    // 右、左、下、上
    static constexpr int dx[4] = {0, 0, 1, -1};
    static constexpr int dy[4] = {1, -1, 0, 0};

    // 將 cost, x, y 打包成一個 int
    inline int pack(int cost, int x, int y) {
        return (cost << 16) | (x << 8) | y;
    }

    // 將 data 解包，轉換成 cost, x, y
    inline std::array<int, 3> unpack(const int &info) {
        return {info >> 16, (info >> 8) & 0xFF, info & 0xFF};
    }

  public:
    int minCost(std::vector<std::vector<int>> &grid) {
        int m = grid.size(), n = grid[0].size();
        // 紀錄從 (0, 0) 走到每個位置的最小成本
        int minCost[m * n];
        std::memset(minCost, 0x3f, sizeof(minCost));
        minCost[0] = 0;
        // 當前所有能到達的點，成本小的在 heap 頂部，存放的數據是 int，前 16 位是成本，後 16 位是位置
        std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
        pq.push({0});

        while (!pq.empty()) {
            std::array<int, 3> info = unpack(pq.top()); // info = {cost, x, y}
            pq.pop();

            // 嘗試往四個方向走
            for (int i = 0; i < 4; ++i) {
                int nx = info[1] + dx[i], ny = info[2] + dy[i];
                // 超出範圍就跳過
                if (nx < 0 || nx >= m || ny < 0 || ny >= n) {
                    continue;
                }
                // 計算新的成本，如果要走的方向和現在的方向不同，則成本 + 1
                int ncost = info[0] + (i + 1 != grid[info[1]][info[2]]);
                // 新的成本比原本的還小才能放入 pq
                if (minCost[nx * n + ny] > ncost) {
                    minCost[nx * n + ny] = ncost;
                    pq.emplace(pack(ncost, nx, ny));
                }
            }
        }

        return minCost[m * n - 1];
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501181606679.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501181606679.png)

#### 複雜度分析

令 $V$ 和 $E$ 分別是有向圖中的節點數和邊數。

- 時間複雜度： $O(m \cdot n \cdot \log(m \cdot n))$

- 空間複雜度： $O(m \cdot n)$

### 2. 0-1 Breadth-First Search

利用所有的路徑成本只有 0 和 1 的特性，對於任何只包含 0 的路徑（無論多長）都會比包含至少一個 1 的路徑還要好，因此應該要先搜索成本為 0 的路徑，等到所有成本為 0 的路徑都走過之後才會考慮成本為 1 的路徑，這種對於傳統的 BFS 修改的演算法稱為 0-1 Breadth-First Search。

相較於傳統 BFS 常用的 queue，0-1 Breadth-First Search 使用 deque 來實作，當路徑的成本為 0 時將其加入至 deque 的頂端，反之則加入至 deque 的尾端，每次將節點取出時都是從頂端來取出，這樣做可以保證每次取出來的節點都是當前成本最小的節點。

由於使用的是 deque，不需要排序，因此不用把節點的 `cost` 和 `xy座標` 打包成一個 int 來儲存，而是直接使用 pair 來儲存，這樣可以節省打包和解包的時間。

#### 程式碼

```cpp {.line=-numbers}
class Solution {
  private:
    // 右、左、下、上
    static constexpr int dx[4] = {0, 0, 1, -1};
    static constexpr int dy[4] = {1, -1, 0, 0};

  public:
    int minCost(std::vector<std::vector<int>> &grid) {
        int m = grid.size(), n = grid[0.].size();
        // 紀錄從 (0, 0) 走到每個位置的最小成本
        int minCost[m * n];
        std::memset(minCost, 0x3f, sizeof(minCost));
        minCost[0] = 0;
        // 當前所有能到達的點，成本小的在 dq 頂部
        std::deque<std::pair<int, int>> dq;
        dq.push_back({0, 0});

        while (!dq.empty()) {
            auto [x, y] = dq.front(); // info = {x, y}
            dq.pop_front();

            // 嘗試往四個方向走
            for (int i = 0; i < 4; ++i) {
                int nx = x + dx[i], ny = y + dy[i];
                // 沒有超出範圍才能進入 dq
                if (nx < 0 || nx >= m || ny < 0 || ny >= n) {
                    continue;
                }
                // 計算新的成本，如果要走的方向和現在的方向不同，則成本 + 1
                int ncost = minCost[x * n + y] + (i + 1 != grid[x][y]);
                //  新的成本比原本的小才能加入 dq
                if (minCost[nx * n + ny] > ncost) {
                    minCost[nx * n + ny] = ncost;
                    // 如果當前路徑成本是 0，則加入 dq 的頂部，反之加入 dq 的尾部
                    i + 1 == grid[x][y] ? dq.push_front({nx, ny}) : dq.push_back({nx, ny});
                }
            }
        }

        return minCost[m * n - 1];
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501181608554.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501181608554.png)

#### 複雜度分析

令 $V$ 和 $E$ 分別是有向圖中的節點數和邊數。

- 時間複雜度： $O(m \cdot n)$

    每個節點最多被加入 `deque` 頭尾各一次。

- 空間複雜度： $O(m \cdot n)$
