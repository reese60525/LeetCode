#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();
class Solution {
  public:
    int coinChange(std::vector<int> &coins, int amount) {
        // 可以用pointer的型態去做，但速度會慢將近一倍
        //  int *dp = new int[amount + 1];
        //  memset(dp, 0x3f, (amount + 1) * sizeof(*dp));
        int dp[amount + 1];
        // 把值全設成0x3f3f3f3f，0x3f3f3f3f常用於表達無窮大。
        memset(dp, 0x3f, sizeof(dp));
        dp[0] = 0;

        for (int i = 1; i <= amount; ++i) // 計算每個dp[n]的最佳解。
            for (auto j : coins)
                if (i >= j)
                    dp[i] = std::min(dp[i], dp[i - j] + 1);

        return dp[amount] != 0x3f3f3f3f ? dp[amount] : -1;
    }
};

int main() { return 0; }