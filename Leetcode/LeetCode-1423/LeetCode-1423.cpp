/*
 * Author      : Reese
 * Created On  : 2024-12-31 21:33
 * Description : https://leetcode.com/problems/maximum-points-you-can-obtain-from-cards/description/
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

// 計算選取的卡片
class Solution {
  public:
    int maxScore(std::vector<int> &cardPoints, int k) {
        int n = cardPoints.size();
        // 計算前 k 張卡片的總和
        int cur_val = std::accumulate(cardPoints.begin(), cardPoints.begin() + k, 0);
        int res = cur_val;

        // 每次迭代都將左右兩端的 window 往左移動一格
        for (int i = k - 1; i >= 0; --i) {
            cur_val -= cardPoints[i];
            cur_val += cardPoints[n - k + i];
            res = std::max(res, cur_val);
        }

        return res;
    }
};

// 計算不選取的卡片
// class Solution {
//   public:
//     int maxScore(std::vector<int> &cardPoints, int k) {
//         int n = cardPoints.size();
//         int x = n - k; // 不選擇的卡片數量

//         int total = 0, cur_sum = 0, min_sum = INT_MAX;
//         for (int i = 0; i < n; ++i) {
//             total += cardPoints[i];
//             cur_sum += cardPoints[i];

//             // 當不選擇的數量滿足 window 大小後才開始計算
//             if (i + 1 >= x) {
//                 min_sum = std::min(min_sum, cur_sum);
//                 cur_sum -= cardPoints[i + 1 - x];
//             }
//         }

//         // x = 0 是例外條件，代表全部選擇，直接回傳 total
//         return x == 0 ? total : total - min_sum;
//     }
// };

int main() {

    return 0;
}
