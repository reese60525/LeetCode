/*
 *  Author      : Reese
 *  Created On  : 2024-12-21 21:31
 *  Description : https://leetcode.com/problems/coin-change-ii/description/
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
    int change(int amount, std::vector<int> &coins) {
        // 需要用 unsigned long long 才能過測資
        unsigned long long dp[amount + 1];
        std::memset(dp, 0, sizeof(dp));
        dp[0] = 1;

        for (size_t i = 0; i < coins.size(); ++i) {
            for (size_t j = coins[i]; j <= amount; ++j) {
                dp[j] += dp[j - coins[i]];
            }
        }

        return dp[amount];
    }
};

int main() {

    return 0;
}