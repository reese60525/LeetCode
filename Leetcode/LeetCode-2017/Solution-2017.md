# <center> [2017. Grid Game](https://leetcode.com/problems/grid-game/submissions/1515225870/) </center>

## 題目敘述

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501211003255.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501211003255.png)

給一個 `2 x n` 的整數矩陣 `grid`，現在有兩個機器人 `A` 和 `B`，倆機器人的起點和終點都是 `grid[0][0]`、`grid[1][n-1]`，並且每次移動只能向右和向下走，這兩個機器人的目標分別為：

- `A` 機器人：其經過的 `grid[i][j]` 會變成 0，目標是要讓 `B` 機器人所經過的**路徑總和最小**。
- `B` 機器人：目標是要讓自己所經過的路徑總和最大。

`A` 機器人會先出發，接著才是 `B` 機器人，兩個機器人所走的路徑都是**最佳路線**。

## 解題思路

### 1. Prefix Sum and  Suffix Sum

觀察機器人 `A` 所行走的路徑，必定會是以下的形式：

- 第一列：`grid[0][0]` -> `grid[0][k]` 都被走過
- 第二列：`grid[1][k]` -> `grid[1][n-1]` 都被走過

就如同下面的例子，0 是機器人 `A` 所走的路徑：

``` text
0 0 0 0 0 ? ? ? ? ?
? ? ? ? 0 0 0 0 0 0
```

可以發現機器人 `B` 能走的路徑就是剩下的 `?` 的部分，由於只能向右和向下移動，為了要讓 `B` 所走的路徑總和最大，那麼 `B` 能走的路線就只有兩種選擇：

1. 將第一列的 `?` 都走過
2. 將第二列的 `?` 都走過

`A` 的目標是為了讓 `B` 的路徑總和最小，令第一列和第二列的 `?` 總和的較大者為 `max`，那麼 `A` 要找出所有路徑中 `max` 的最小值，這就會是 `B` 所走的路徑總和。

綜合以上分析，我們可以遍歷 `grid` ，計算出第一列和第二列的 `?` 總和，並更新 `max` 的值來求解。

#### 程式碼

```cpp {.line-numbers}
class Solution {
  public:
    long long gridGame(std::vector<std::vector<int>> &grid) {
        int n = grid[0].size(); // 每一列的長度
        // top 和 bottom 分別是第一列和第二列的 `?` 總和
        long long top = std::accumulate(grid[0].begin(), grid[0].end(), 0l);
        long long bottom = 0;

        // 遍歷 grid 找出能讓 B 路徑總和最小的值
        long long res = LLONG_MAX;
        for (int i = 0; i < n; ++i) {
            top -= grid[0][i];
            res = std::min(res, std::max(top, bottom));
            bottom += grid[1][i];
        }

        return res;
    }
};
```

[![](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501211023773.png)](https://raw.githubusercontent.com/reese60525/ForPicGo/main/ForPicGo/Pictures/202501211023773.png)

令 $n$ 為 `grid` 的列長度，

- 時間複雜度： $O(n)$

- 空間複雜度： $O(1)$
