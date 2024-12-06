#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    int coinChange(std::vector<int> &coins, int amount) {
        std::vector<int> dp(amount + 1, 0x3f3f3f);
        dp[0] = 0;

        for (int i = 0; i < coins.size(); ++i) {
            for (int j = coins[i]; j <= amount; ++j) {
                dp[j] = std::min(dp[j], dp[j - coins[i]] + 1);
            }
        }

        return dp[amount] == 0x3f3f3f ? -1 : dp[amount];
    }
};

int main() {

    return 0;
}