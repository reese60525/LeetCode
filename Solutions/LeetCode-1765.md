# <center> [1765. Map of Highest Peak](https://leetcode.com/problems/map-of-highest-peak/description/) </center>

## 題目敘述

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501222158795.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501222158795.png)

給一個二為整數陣列 `isWater`，其中 `isWater[i][j]` 如果是 0 表示是陸地，如果是 1 表示是水域，需要根據以下規則來分配每個位置的高度：

1. 每個水域的高度必須是 0。
2. 每個相鄰區域（上下左右）的高度差最多為 1。

請找出能讓矩陣中的最高高度最大化的分配方式。

## 解題思路

### 1. Breadth First Search（BFS）

題目要求水域的高度必須為 0，因此可以將所有水域當作起始點向外擴張每個區域的高度，直到所有區域都被分配到高度。

那麼這道題目就是一個簡單的**多源點 BFS** 問題，演算法流程如下：

1. 首先遍歷 `isWater` 矩陣，將所有水域的位置加入至 queue 中，並且如果當前位置是水域，將其高度設為 0，若是陸地則設為 -1 表示尚未被分配高度。

2. 接著開始 BFS，每次從 queue 中取出一個位置，並且檢查其周圍四個方向的位置，如果該位置沒有超出邊界並且尚未被分配到高度，則將其高度設為當前位置的高度加 1，然後把該位置加入 queue 中。

3. 重複步驟 2 直到 queue 為空，此時所有位置的高度都已經被分配完畢，return `isWater` 矩陣即可。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    std::vector<std::vector<int>> highestPeak(std::vector<std::vector<int>> &isWater) {
        int r = isWater.size(), c = isWater[0].size();
        std::queue<int> q;
        // 將所有水域加入至 queue 中，並修改 isWater 的值方便後續計算
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                if (isWater[i][j]) {
                    isWater[i][j] = 0;
                    q.push((i << 16) | j);
                }
                else {
                    isWater[i][j] = -1;
                }
            }
        }

        // BFS 更新每個位置的高度
        int dir[5] = {0, 1, 0, -1, 0}; // 右、下、左、上
        while (!q.empty()) {
            int size = q.size();
            while (size--) {
                int x = q.front() >> 16, y = q.front() & 0xffff;
                q.pop();

                for (int i = 0; i < 4; ++i) {
                    int nx = x + dir[i], ny = y + dir[i + 1];
                    // 判斷是否超出邊界或是已經走過
                    if (nx >= 0 && nx < r && ny >= 0 && ny < c && isWater[nx][ny] == -1) {
                        isWater[nx][ny] = isWater[x][y] + 1;
                        q.push((nx << 16) | ny);
                    }
                }
            }
        }

        return isWater;
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501222214391.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501222214391.png)

#### 複雜度分析

令 `m` 為 `isWater` 的列數，`n` 為 `isWater` 的行數。

- 時間複雜度： $O(m \cdot n)$

    需要遍歷整個 `m x n` 矩陣。

- 空間複雜度： $O(m \cdot n)$

    最壞情況下所有位置都是水域，此時需要將整個 `m x n` 矩陣加入 queue 中。

### 2. Dynamic Programming（DP）

將這個問題換個角度來看，可以將每個位置的高度視為該位置到**最近水域**的距離，而共有四種方向的水域需要考慮，令 `dp[i][j]` 表示位置 `(i, j)` 到最近水域的距離，則有以下狀態轉移方程式：

$$
dp[i][j] = \min(dp[i - 1][j], dp[i + 1][j], dp[i][j - 1], dp[i][j + 1]) + 1
$$

共有四種方向需要檢查，可以分為兩次遍歷來更新 `dp` 矩陣：

1. 從左上到右下，在這次遍歷中計算左方和上方最近的水域距離。

2. 從右下到左上，在這次遍歷中計算右方和下方最近的水域距離。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    std::vector<std::vector<int>> highestPeak(std::vector<std::vector<int>> &isWater) {
        int r = isWater.size(), c = isWater[0].size();
        std::vector<std::vector<int>> dp(r, std::vector<int>(c, 0x3f3f3f3f));

        // 先將水域的值設為 0
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                if (isWater[i][j] == 1) {
                    dp[i][j] = 0;
                }
            }
        }

        // 從左上到右下更新 dp
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                if (i > 0) {
                    dp[i][j] = std::min(dp[i][j], dp[i - 1][j] + 1);
                }
                if (j > 0) {
                    dp[i][j] = std::min(dp[i][j], dp[i][j - 1] + 1);
                }
            }
        }
        /// 從右下到左上更新 dp
        for (int i = r - 1; i >= 0; --i) {
            for (int j = c - 1; j >= 0; --j) {
                if (i < r - 1) {
                    dp[i][j] = std::min(dp[i][j], dp[i + 1][j] + 1);
                }
                if (j < c - 1) {
                    dp[i][j] = std::min(dp[i][j], dp[i][j + 1] + 1);
                }
            }
        }

        return dp;
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501222254322.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501222254322.png)

也可以使用 lambda 函式來簡化程式碼，但判斷條件變多因此效率較差

```cpp {.line-numbers}
class Solution {
  public:
    std::vector<std::vector<int>> highestPeak(std::vector<std::vector<int>> &isWater) {
        int r = isWater.size(), c = isWater[0].size();
        std::vector<std::vector<int>> dp(r, std::vector<int>(c, 0x3f3f3f3f));

        // 先將水域的值設為 0
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                if (isWater[i][j] == 1) {
                    dp[i][j] = 0;
                }
            }
        }

        auto func = [&](int x, int y, int dx, int dy) {
            for (int i = x; i > -1 && i < r; i += dx) {
                for (int j = y; j > -1 && j < c; j += dy) {
                    if (i - dx > -1 && i - dx < r) {
                        dp[i][j] = std::min(dp[i][j], dp[i - dx][j] + 1);
                    }
                    if (j - dy > -1 && j - dy < c) {
                        dp[i][j] = std::min(dp[i][j], dp[i][j - dy] + 1);
                    }
                }
            }
        };

        func(0, 0, 1, 1);
        func(r - 1, c - 1, -1, -1);

        return dp;
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501222301619.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501222301619.png)

#### 複雜度分析

令 `m` 為 `isWater` 的列數，`n` 為 `isWater` 的行數。

- 時間複雜度： $O(m \cdot n)$

    需要遍歷整個 `m x n` 矩陣。

- 空間複雜度： $O(m \cdot n)$

    需要使用一個 `m x n` 的矩陣來儲存每個位置到最近水域的距離。
