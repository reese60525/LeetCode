/*
 *  Author      : Reese
 *  Created On  : 2024-12-31 10:59
 *  Description : https://leetcode.com/problems/minimum-cost-for-tickets/description/
 */

#include <iostream>
#include <vector>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    int mincostTickets(std::vector<int> &days, std::vector<int> &costs) {
        // dp[k] 表示前 k 個旅遊天所需要的最小車票花費
        int dp[days.size() + 1];
        dp[0] = 0;

        for (int i = 1; i <= days.size(); ++i) {
            // 前 i 個旅遊在 days 中的 index 要變成 i - 1
            // 例如：前 4 個旅遊在 days 中的 index 為 {0, 1, 2, 3}
            // 將已經買了目前的車票的 day 略過
            int idx7 = i - 1, idx30 = i - 1;
            while (--idx7 >= 0 && days[i - 1] - days[idx7] < 7) {}
            while (--idx30 >= 0 && days[i - 1] - days[idx30] < 30) {}
            // 因為 dp[k] 的 k 是指第 k 個旅遊天，所以要把 days index 再 + 1
            dp[i] = std::min({dp[i - 1] + costs[0], dp[idx7 + 1] + costs[1], dp[idx30 + 1] + costs[2]});
        }

        return dp[days.size()];
    }
};

int main() {

    return 0;
}