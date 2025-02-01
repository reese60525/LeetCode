/*
 * 題目： https://leetcode.com/problems/minimum-obstacle-removal-to-reach-corner/description/
 *
 * 題目解釋：
 * 給一個整數matrix，其中0代表空地，1代表障礙物，可以將障礙物移除，求從左上角(0, 0)到
 * 右下角(m-1, n-1)所需要移除的最少障礙物數量。
 * e.g.
 *          {0, 1, 1}                                          {0, 0, 0}
 * matrix = {1, 1, 0} ，可以將(0, 1)、(0, 2)的障礙物移除，會變成 {1, 1, 0}，因此答案為2。
 *          {1, 1, 0}                                         {1, 1, 0}
 *
 * 思路：
 * 用0-1 bfs algorithm，這是用來專門處理graph中邊的權重只有0或1的演算法，與傳統的bfs相比，
 * 0-1 bfs會判斷當前的children node的權重，如果是0就將該node放到queue的前端，若是1則放入，
 * queue的後端，因此形成一個權重由小到大的queue，會優先處理權重小的node(邊)，用於搜尋權重
 * 最小的路徑很方便，該演算法"只能用於邊的權重只有0和1"。
 */
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    int minimumObstacles(std::vector<std::vector<int>> &grid) {
        int m = grid.size(), n = grid[0].size();
        int dir[5] = {0, 1, 0, -1, 0};            // 方向:右、下、左、上
        std::deque<std::tuple<int, int, int>> dq; // <row, col, 障礙物數量>
        dq.push_back({0, 0, 0});
        grid[0][0] = -1; // visited

        while (!dq.empty()) {
            auto [x, y, weight] = dq.front();
            dq.pop_front();

            // 抵達終點
            if (x == m - 1 && y == n - 1) {
                return weight;
            }

            for (int i = 0; i < 4; ++i) {
                int nx = x + dir[i], ny = y + dir[i + 1]; // 下個位置
                if (nx >= 0 && nx < m && ny >= 0 && ny < n && grid[nx][ny] != -1) {
                    // 因為要找最少障礙物數量，優先走空地，再走障礙物
                    if (grid[nx][ny] == 0) {
                        // 該點沒有障礙物，因此走到該點的障礙物(weight) + 0
                        dq.push_front({nx, ny, weight + 0});
                    }
                    else if (grid[nx][ny] == 1) {
                        // 該點有障礙物，因此走到該點的障礙物(weight) + 1
                        dq.push_back({nx, ny, weight + 1});
                    }
                    grid[nx][ny] = -1; // visited
                }
            }
        }

        return -1; // 無法抵達終點
    }
};

int main() {

    return 0;
}