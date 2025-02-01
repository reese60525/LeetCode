# <center> [200. Number of Islands](https://leetcode.com/problems/number-of-islands/description/) </center>

## 題目敘述

[![](https://i.imgur.com/C7DPaCM.png)](https://i.imgur.com/C7DPaCM.png)

給一個由 0 和 1 組成的 $m \times n$ 的矩陣，0 表示海水、1表示陸地，所有相鄰的（上下左右）陸地視為同一個大陸，請問共有幾個大陸？

- 矩陣邊緣（邊界外）視為被海水所包覆

## 解題思路

### 1. DFS

遍歷 `grid`，對於 $grid[i][j] = 1$ 的陸地進行 DFS，將所有相鄰的陸地全變為 0 表示已經探索過，然後大陸數量 + 1，遍歷整個 `grid` 後即可算出大陸的數量。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    int M, N; // 矩陣的列數、行數

    void dfs(int i, int j, std::vector<std::vector<char>> &grid) {
        // 判斷是否超出邊界，以及是否已經走過或是該位置是海洋
        if (i < 0 || i >= M || j < 0 || j >= N || grid[i][j] == '0') {
            return;
        }

        grid[i][j] = '0'; // 將當前位置改為海水，表示已經走過
        // 往四周繼續尋找相鄰陸地
        dfs(i + 1, j, grid);
        dfs(i - 1, j, grid);
        dfs(i, j + 1, grid);
        dfs(i, j - 1, grid);
    };

    int numIslands(std::vector<std::vector<char>> &grid) {
        M = grid.size(), N = grid[0].size();

        // 遍歷 grid，用 DFS 將同個大陸的陸地都標記表示已經走過
        int res = 0;
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                if (grid[i][j] == '1') {
                    ++res;
                    dfs(i, j, grid);
                }
            }
        }

        return res;
    }
};
```

[![](https://i.imgur.com/wBWSolP.png)](https://i.imgur.com/wBWSolP.png)

#### 複雜度分析

令 $m$ 、 $n$ 分別為 `grid` 的列數、行數。

- 時間複雜度： $O(m \cdot n)$

    每個位置最多被訪問一次。

- 空間複雜度： $O(m \cdot n)$

    若 `grid` 為 $1 \times n$ 且全為 1，最多需要 $m \times n$ 的遞迴 stack 空間。

### 2. BFS

一樣的思路，只不過以 BFS 取代 DFS。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    int M, N; // 矩陣的列數、行數
    static constexpr int dir[5] {1, 0, -1, 0, 1};

    void bfs(int i, int j, std::vector<std::vector<char>> &grid) {
        std::queue<std::pair<int, int>> q;
        q.push({i, j});
        grid[i][j] = '0';

        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();

            for (int k = 0; k < 4; ++k) {
                int nx = x + dir[k], ny = y + dir[k + 1];
                // 判斷是否超出邊界，以及是否已經走過或是該位置是海洋
                if (nx < 0 || nx >= M || ny < 0 || ny >= N || grid[nx][ny] == '0') {
                    continue;
                }
                grid[nx][ny] = '0'; // 標記該陸地為已經走過
                q.push({nx, ny});
            }
        }
    };

    int numIslands(std::vector<std::vector<char>> &grid) {
        M = grid.size(), N = grid[0].size();

        // 遍歷 grid，用 BFS 將同個大陸的陸地都標記表示已經走過
        int res = 0;
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                if (grid[i][j] == '1') {
                    ++res;
                    bfs(i, j, grid);
                }
            }
        }

        return res;
    }
};
```

[![](https://i.imgur.com/mFpKjGn.png)](https://i.imgur.com/mFpKjGn.png)

#### 複雜度分析

令 $m$ 、 $n$ 分別為 `grid` 的列數、行數。

- 時間複雜度： $O(m \cdot n)$

    每個位置最多被訪問一次。

- 空間複雜度： $O(m \cdot n)$

    若 `grid` 為 $1 \times n$ 且全為 1，則 `queue` 最多需要 $m \times n$ 的空間。
