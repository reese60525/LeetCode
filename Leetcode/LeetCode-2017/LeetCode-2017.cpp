/*
 *  Author      : Reese
 *  Created On  : 2025-01-21 09:18
 *  Description : https://leetcode.com/problems/grid-game/description/
 */

#include <climits>
#include <iostream>
#include <numeric>
#include <vector>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

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

int main() {

    return 0;
}