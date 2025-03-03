```cpp
/*
 *  Author      : Reese
 *  Created On  : 2025-01-27 19:46
 *  Description : https://leetcode.com/problems/maximum-number-of-fish-in-a-grid/description/
 */

#include <iostream>
#include <queue>
#include <vector>

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,abm,bmi2")

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

// DFS
class Solution {
  public:
    int findMaxFish(std::vector<std::vector<int>> &grid) {
        int m = grid.size(), n = grid[0].size();
        int res = 0;

        auto dfs = [&](this auto dfs, int i, int j) -> int {
            if (i < 0 || i >= m || j < 0 || j >= n || grid[i][j] == 0) {
                return 0;
            }

            int temp = grid[i][j];
            grid[i][j] = 0;
            return temp + dfs(i + 1, j) + dfs(i - 1, j) + dfs(i, j + 1) + dfs(i, j - 1);
        };

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                res = std::max(res, dfs(i, j));
            }
        }

        return res;
    }
};

// BFS
class Solution1 {
  private:
    static constexpr int dir[5] = {-1, 0, 1, 0, -1};

  public:
    int findMaxFish(std::vector<std::vector<int>> &grid) {
        int m = grid.size(), n = grid[0].size();
        int res = 0;
        std::queue<std::pair<int, int>> q;

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                // 如果當前格子沒有魚或是是陸地則跳過
                if (grid[i][j] == 0) {
                    continue;
                }

                // BFS 計算該區域所有魚隻數量
                int total = grid[i][j];
                grid[i][j] = 0;
                q.push({i, j});
                while (!q.empty()) {
                    auto [x, y] = q.front();
                    q.pop();
                    // 往四個方向擴展
                    for (int k = 0; k < 4; ++k) {
                        int nx = x + dir[k], ny = y + dir[k + 1];
                        if (nx >= 0 && nx < m && ny >= 0 && ny < n && grid[nx][ny]) {
                            total += grid[nx][ny];
                            grid[nx][ny] = 0;
                            q.push({nx, ny});
                        }
                    }
                }

                // 更新最多能捕獲的魚數量
                res = std::max(res, total);
            }
        }

        return res;
    }
};

int main() {

    return 0;
}
```
