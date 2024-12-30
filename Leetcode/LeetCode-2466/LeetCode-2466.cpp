/*
 *  Author      : Reese
 *  Created On  : 2024-12-30 07:31
 *  Description : https://leetcode.com/problems/count-ways-to-build-good-strings/description/
 */

#include <iostream>
#include <numeric>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    int countGoodStrings(int low, int high, int zero, int one) {
        const int N = 1000000007;
        // 優化查找範圍，以 GCD 來壓縮範圍
        int g = std::gcd(zero, one);
        low += g - 1; // 為了處理向上取整
        zero /= g, one /= g, low /= g, high /= g;

        int dp[high + 1];
        std::memset(dp, 0, sizeof(dp));

        for (int i = high; i >= 0; --i) {
            // 要記得處理邊界條件
            dp[i] += (i >= low);
            dp[i] += (i + zero <= high) ? dp[i + zero] : 0;
            dp[i] += (i + one <= high) ? dp[i + one] : 0;
            dp[i] %= N;
        }

        return dp[0];
    }
};

int main() {

    return 0;
}