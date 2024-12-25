/*
 *  Author      : Reese
 *  Created On  : 2024-12-25 10:13
 *  Description : https://leetcode.com/problems/minimum-cost-for-cutting-cake-i/description/
 */

#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <vector>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

// Priority Queue
class Solution {
  public:
    int minimumCost(int m, int n, std::vector<int> &horizontalCut, std::vector<int> &verticalCut) {
        int h_cnt = 1, v_cnt = 1;                     // 計算蛋糕目前在水平方向和垂直方向共被切成幾塊
        std::priority_queue<std::pair<int, bool>> pq; // 儲存所有切割成本，queue top 為最大的成本

        // 將垂直和水平分割的成本放入 pq 中
        // is_row 用來判斷該分割成本是水平還是垂直的分割成本
        auto buildPQ = [&](std::vector<int> arr, bool is_row) -> void {
            for (size_t i = 0; i < arr.size(); ++i) {
                pq.push({arr[i], is_row});
            }
        };
        buildPQ(horizontalCut, true);
        buildPQ(verticalCut, false);

        // 計算總成本
        int res = 0;
        while (!pq.empty()) {
            auto [cost, is_row] = pq.top();
            pq.pop();

            // 成本計算方式為： 該次切割成本 * 該方向上有幾個蛋糕
            // 例如要切水平方向的蛋糕，則這次切割的總成本 = 切割成本 * 目前垂直方向上有幾個蛋糕
            res += is_row ? cost * v_cnt : cost * h_cnt;
            // 更新目前水平和垂直方向上有幾個蛋糕
            h_cnt += is_row;
            v_cnt += !is_row;
        }

        return res;
    }
};

// // Two Pointer
// class Solution {
//   public:
//     int minimumCost(int m, int n, std::vector<int> &horizontalCut, std::vector<int> &verticalCut) {
//         // 要由大排到小
//         std::sort(horizontalCut.begin(), horizontalCut.end(), std::greater<int>());
//         std::sort(verticalCut.begin(), verticalCut.end(), std::greater<int>());

//         // h_cnt 和 v_cnt 分別代表目前水平和垂直方向上有幾個蛋糕
//         int i = 0, j = 0, h_cnt = 1, v_cnt = 1, res = 0;
//         while (i < m - 1 || j < n - 1) {
//             // 邊界判斷避免 index out of range
//             int h_cost = i < m - 1 ? horizontalCut[i] : 0;
//             int v_cost = j < n - 1 ? verticalCut[j] : 0;
//             // 判斷目前哪個成本比較大，並將該成本計入總成本中
//             bool is_h_bigger = h_cost > v_cost;
//             res += is_h_bigger ? h_cost * v_cnt : v_cost * h_cnt;
//             // 更新 index 和 目前水平和垂直方向上有幾個蛋糕
//             is_h_bigger ? ++i : ++j;
//             is_h_bigger ? ++h_cnt : ++v_cnt;
//         }

//         return res;
//     }
// };

int main() {

    return 0;
}