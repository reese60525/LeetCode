/*
 *  Author      : Reese
 *  Created On  : 2025-01-18 08:24
 *  Description : https://leetcode.com/problems/minimum-cost-to-make-at-least-one-valid-path-in-a-grid/description/
 */

#include <climits>
#include <deque>
#include <functional>
#include <iostream>
#include <queue>
#include <vector>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

// Dijkstra Algorithm
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

// 0-1 BFS
// class Solution {
//   private:
//     // 右、左、下、上
//     static constexpr int dx[4] = {0, 0, 1, -1};
//     static constexpr int dy[4] = {1, -1, 0, 0};

//   public:
//     int minCost(std::vector<std::vector<int>> &grid) {
//         int m = grid.size(), n = grid[0.].size();
//         // 紀錄從 (0, 0) 走到每個位置的最小成本
//         int minCost[m * n];
//         std::memset(minCost, 0x3f, sizeof(minCost));
//         minCost[0] = 0;
//         // 當前所有能到達的點，成本小的在 dq 頂部
//         std::deque<std::pair<int, int>> dq;
//         dq.push_back({0, 0});

//         while (!dq.empty()) {
//             auto [x, y] = dq.front(); // info = {x, y}
//             dq.pop_front();

//             // 嘗試往四個方向走
//             for (int i = 0; i < 4; ++i) {
//                 int nx = x + dx[i], ny = y + dy[i];
//                 // 沒有超出範圍才能進入 dq
//                 if (nx < 0 || nx >= m || ny < 0 || ny >= n) {
//                     continue;
//                 }
//                 // 計算新的成本，如果要走的方向和現在的方向不同，則成本 + 1
//                 int ncost = minCost[x * n + y] + (i + 1 != grid[x][y]);
//                 //  新的成本比原本的小才能加入 dq
//                 if (minCost[nx * n + ny] > ncost) {
//                     minCost[nx * n + ny] = ncost;
//                     // 如果當前路徑成本是 0，則加入 dq 的頂部，反之加入 dq 的尾部
//                     i + 1 == grid[x][y] ? dq.push_front({nx, ny}) : dq.push_back({nx, ny});
//                 }
//             }
//         }

//         return minCost[m * n - 1];
//     }
// };

int main() {

    return 0;
}