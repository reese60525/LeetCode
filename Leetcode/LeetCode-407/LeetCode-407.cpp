/*
 *  Author      : Reese
 *  Created On  : 2025-01-19 10:02
 *  Description : https://leetcode.com/problems/trapping-rain-water-ii/description/
 */

#include <iostream>
#include <queue>
#include <vector>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  private:
    // 將柱子的數據打包成整數來儲存
    static inline int pack(const int &height, const int &x, const int &y) {
        return (height << 16) | (x << 8) | y;
    }
    // 將柱子數據解包
    static inline std::array<int, 3> unpack(const int &packed) {
        return {packed >> 16, (packed >> 8) & 0xff, packed & 0xff};
    }

  public:
    int trapRainWater(std::vector<std::vector<int>> &heightMap) {
        int r = heightMap.size(), c = heightMap[0].size();
        // pq 存放當前的邊界，將 pq 中的邊界以高度由小排到大
        std::priority_queue<int, std::vector<int>, std::greater<int>> pq;

        // 將矩陣初始的邊界加入至 pq
        for (int i = 0; i < c; ++i) {
            pq.push(pack(heightMap[0][i], 0, i));
            pq.push(pack(heightMap[r - 1][i], r - 1, i));
            heightMap[0][i] = heightMap[r - 1][i] = -1; // 將拜訪過的柱子標記為 -1
        }
        for (int i = 1; i < r - 1; ++i) {
            pq.push(pack(heightMap[i][0], i, 0));
            pq.push(pack(heightMap[i][c - 1], i, c - 1));
            heightMap[i][0] = heightMap[i][c - 1] = -1; // 將拜訪過的柱子標記為 -1
        }

        // 從 pq 中取出柱子，並更新邊界和計算能夠儲存的雨水總量
        int res = 0;
        int dirs[5] = {-1, 0, 1, 0, -1}; // 上、右、下、左
        while (!pq.empty()) {
            auto [height, x, y] = unpack(pq.top());
            pq.pop();

            // 檢查四周的柱子
            for (int i = 0; i < 4; ++i) {
                int nx = x + dirs[i], ny = y + dirs[i + 1];
                // 超出邊界或是拜訪過的就跳過
                if (nx < 0 || nx >= r || ny < 0 || ny >= c || heightMap[nx][ny] == -1) {
                    continue;
                }

                int nheight = std::max(height, heightMap[nx][ny]); // 計算接雨水後的高度
                res += std::max(0, height - heightMap[nx][ny]);    // 計算該柱子能接多少雨水
                pq.push(pack(nheight, nx, ny));                    // 將該柱子當作新的邊界加入至 pq
                heightMap[nx][ny] = -1;                            // 標記該柱子已經拜訪過
            }
        }

        return res;
    }
};

int main() {

    return 0;
}