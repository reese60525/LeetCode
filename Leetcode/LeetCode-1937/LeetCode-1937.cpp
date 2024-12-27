/*
 *  Author      : Reese
 *  Created On  : 2024-12-27 12:04
 *  Description : https://leetcode.com/problems/maximum-number-of-points-with-cost/description/
 */

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <vector>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    long long maxPoints(std::vector<std::vector<int>> &points) {
        int m = points.size(), n = points[0].size();

        // 初始化 dp
        long long dp[n];
        for (int i = 0; i < n; ++i) {
            dp[i] = points[0][i];
        }

        // 迭代更新每一層 dp
        for (int i = 1; i < m; ++i) {
            // prefix max
            long long left_max = 0;
            // suffix max
            long long right_max[n];
            right_max[n - 1] = dp[n - 1];
            for (long long j = n - 2; j >= 0; --j) {
                right_max[j] = std::max(right_max[j + 1] - 1, dp[j]);
            }

            for (int j = 0; j < n; ++j) {
                left_max = std::max(left_max - 1, dp[j]); // 更新 prefix max
                dp[j] = points[i][j] + std::max(left_max, right_max[j]);
            }
        }

        long long res = 0;
        for (int i = 0; i < n; ++i) {
            res = std::max(res, dp[i]);
        }

        return res;
    }
};

int main() {

    return 0;
}