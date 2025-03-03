# <center> [827. Making A Large Island](https://leetcode.com/problems/making-a-large-island/description/) </center>

## 題目敘述

[![](https://i.imgur.com/Y177snh.png)](https://i.imgur.com/Y177snh.png)

給一個由 0 和 1 組成的 $n \times n$ 的整數矩陣 `grid`，0 表示海、1 表示陸地，定義一個島嶼為 **所有相鄰（上下左右）的陸地** 所組成。

可以將 `grid` 中任一個 0 變 1，也就是海洋變成陸地，**該操作只能做一次**，請問 `grid` 中的島嶼面積最大是多少？

## 解題思路

### 1. DFS

先計算出每個島嶼的面積，並紀錄所有陸地屬於哪個島嶼。接著遍歷 `grid`，若當前區域是陸地，則和該區所屬的島嶼面積比較，若是海洋，計算該海洋變成陸地後其上下左右的島嶼面積總和再比較，找出面積總和最大值即為答案。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    int largestIsland(std::vector<std::vector<int>> &grid) {
        int groupId = -1, n = grid.size(); // 島嶼編號為 -1, -2, -3 ... 方便計算
        int groupSize[n * n / 2 + 5];      // 紀錄每個島嶼的面積，編號 -1 的島嶼面積為 groupSize[1]
        std::memset(groupSize, 0, sizeof(groupSize));

        // dfs 遍歷整個島嶼，計算面積並紀錄每個陸地所屬的島嶼編號
        auto dfs = [&](this auto &&dfs, int i, int j) -> int {
            if (i < 0 || i >= n || j < 0 || j >= n || grid[i][j] < 1) {
                return 0;
            }
            grid[i][j] = groupId; // 更新當前陸地的島嶼編號
            return 1 + dfs(i + 1, j) + dfs(i - 1, j) + dfs(i, j + 1) + dfs(i, j - 1);
        };

        // 遍歷 grid 中所有島嶼，用 dfs 遍歷整個島嶼
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] > 0) {
                    // ~(positive integer) + 1 = negative integer
                    // ~(negative integer - 1) = positive integer
                    groupSize[~(groupId - 1)] = dfs(i, j);
                    --groupId;
                }
            }
        }

        // 遍歷 grid，找出最大面積
        int res = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                // 若當前區域是陸地，則將 res 和其所屬島嶼的面積比較取較大者
                if (grid[i][j] != 0) {
                    res = std::max(res, groupSize[~(grid[i][j] - 1)]);
                    continue;
                }

                int cur = 1; // 當前島嶼面積（海洋變島嶼）
                // 計算四周島嶼的編號，若超出邊界則設為 0（groupSize[0] = 0）
                int a = (i > 0) ? ~(grid[i - 1][j] - 1) : 0;
                int b = (i + 1 < n) ? ~(grid[i + 1][j] - 1) : 0;
                int c = (j > 0) ? ~(grid[i][j - 1] - 1) : 0;
                int d = (j + 1 < n) ? ~(grid[i][j + 1] - 1) : 0;

                // 累加四周的島嶼面積，並且要判斷每個島嶼是否已經重複（相同島嶼）
                cur += groupSize[a];
                if (b != a) {
                    cur += groupSize[b];
                }
                if (c != a && c != b) {
                    cur += groupSize[c];
                }
                if (d != a && d != b && d != c) {
                    cur += groupSize[d];
                }

                // 更新最大島嶼面積
                res = std::max(res, cur);
            }
        }

        return res;
    }
};
```

[![](https://i.imgur.com/1Tak3db.png)](https://i.imgur.com/1Tak3db.png)

#### 複雜度分析

令 $n$ 為 `grid` 的列數、行數。

- 時間複雜度： $O(n^2)$

    計算島嶼面積需要遍歷整個 `grid`，需要 $O(n^2)$ ，枚舉所有海洋也需要遍歷整個 `grid`，需要 $O(n^2)$ ，整體需要 $O(n^2)$ 。

- 空間複雜度： $O(n^2)$

    紀錄島嶼面積 `groupSize` 需要 $O(n^2)$ 空間。

### 2. Disjoint Set Union（DSU）

思路一樣，將 DFS 改用 DSU 來做。

```cpp {.line-numbers}
class DSU {
  private:
    int root[505 * 505];      // 紀錄每個位置的 root
    int groupSize[505 * 505]; // 紀錄每個島嶼的面積

  public:
    DSU() {
        for (int i = 0; i < 505 * 505; ++i) {
            root[i] = i;
            groupSize[i] = 1;
        }
    }

    // 查找 root，並將路徑壓縮
    int find(int x) {
        return x == root[x] ? x : root[x] = find(root[x]);
    }

    // 將兩個集合進行合併（by size）
    void connect(int a, int b) {
        int fa = find(a), fb = find(b);

        if (fa == fb) {
            return;
        }
        else if (groupSize[fa] > groupSize[fb]) {
            root[fb] = fa;
            groupSize[fa] += groupSize[fb];
        }
        else {
            root[fa] = fb;
            groupSize[fb] += groupSize[fa];
        }
    }

    // 取得島嶼的面積
    int getSize(int x) {
        return groupSize[find(x)];
    }
};

class Solution {
  private:
    static constexpr int dir[5] = {0, 1, 0, -1, 0};

  public:
    int largestIsland(std::vector<std::vector<int>> &grid) {
        int n = grid.size();
        DSU dsu;

        // 遍歷 grid 中所有島嶼，將相鄰陸地連結到同個集合
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 0) {
                    continue;
                }

                // 若當前位置是陸地，將四周也是陸地的區域合併
                for (int k = 0; k < 4; ++k) {
                    int ni = i + dir[k], nj = j + dir[k + 1];
                    if (ni < 0 || ni >= n || nj < 0 || nj >= n || grid[ni][nj] == 0) {
                        continue;
                    }
                    dsu.connect(i * n + j, ni * n + nj);
                }
            }
        }

        // 遍歷 grid，找出最大面積
        int res = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                // 若當前區域是陸地，則將 res 和其所屬島嶼的面積比較取較大者
                if (grid[i][j]) {
                    res = std::max(res, dsu.getSize(i * n + j));
                    continue;
                }

                int cur = 1; // 當前島嶼面積（海洋變島嶼）
                // 計算四周島嶼的編號，若超出邊界或是海洋區域則設為 -1
                int a = (i > 0 && grid[i - 1][j] != 0) ? dsu.find((i - 1) * n + j) : -1;
                int b = (i + 1 < n && grid[i + 1][j] != 0) ? dsu.find((i + 1) * n + j) : -1;
                int c = (j > 0 && grid[i][j - 1] != 0) ? dsu.find(i * n + (j - 1)) : -1;
                int d = (j + 1 < n && grid[i][j + 1] != 0) ? dsu.find(i * n + (j + 1)) : -1;

                // 累加四周的島嶼面積，並且要判斷每個島嶼是否已經重複（相同島嶼）
                if (a != -1) {
                    cur += dsu.getSize(a);
                }
                if (b != -1 && b != a) {
                    cur += dsu.getSize(b);
                }
                if (c != -1 && c != a && c != b) {
                    cur += dsu.getSize(c);
                }
                if (d != -1 && d != a && d != b && d != c) {
                    cur += dsu.getSize(d);
                }

                // 更新最大島嶼面積
                res = std::max(res, cur);
            }
        }

        return res;
    }
};
```

[![](https://i.imgur.com/VXBBvVx.png)](https://i.imgur.com/VXBBvVx.png)

#### 複雜度分析

- 時間複雜度： $O(n^2 \cdot \alpha(n^2))$

    計算島嶼面積需要遍歷整個 `grid`，需要 $O(n^2)$ ，對每個陸地查詢 `root` 需要 $O(\alpha(n^2))$ ，因此共需要 $O(n^2 \cdot \alpha(n^2))$ 。

- 空間複雜度： $O(n^2)$

    紀錄島嶼面積的 `groupSize` 和所屬集合 `root` 需要 $O(n^2)$ 空間。
