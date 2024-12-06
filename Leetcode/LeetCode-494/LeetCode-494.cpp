#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    int findTargetSumWays(std::vector<int> &nums, int target) {
        // 計算 nums 和 sum 的總和
        int sum = target;
        for (int n : nums) {
            sum += n;
        }

        // 若總和為負數或是奇數，表示此題無解
        if (sum < 0 || sum % 2 == 1) {
            return 0;
        }

        sum /= 2; // positive = sum / 2
        // 改成一維陣列
        std::vector<int> dp(sum + 1, 0);
        dp[0] = 1; // 初始狀態

        // 計算每個 dp[i][j] 的解
        for (int i = 0; i < nums.size(); ++i) {
            // 從後面開始計算，j < nums[i] 的值不會被改變因此不用計算
            for (int j = sum; j >= nums[i]; --j) {
                dp[j] = dp[j] + dp[j - nums[i]];
            }
        }

        return dp[sum];
    }
};

int main() {

    return 0;
}