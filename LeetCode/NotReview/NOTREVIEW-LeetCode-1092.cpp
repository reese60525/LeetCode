/*
 *  Author      : Reese
 *  Created On  : 2025-02-28 13:25
 *  Description : https://leetcode.com/problems/shortest-common-supersequence/description/
 */

#include <algorithm>
#include <iostream>

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,abm,bmi2")

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    auto shortestCommonSupersequence(std::string &str1, std::string &str2) -> std::string {
        int m = str1.size(), n = str2.size();
        int dp[m + 1][n + 1];
        std::memset(dp, 0, sizeof(dp));

        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (str1[i - 1] == str2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                } else {
                    dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }

        int i = m, j = n;
        std::string res;
        res.reserve(m + n);
        while (i > 0 || j > 0) {
            if (i > 0 && j > 0 && str1[i - 1] == str2[j - 1]) {
                res += str1[--i], --j;
            } else if (j == 0 || (i > 0 && dp[i - 1][j] > dp[i][j - 1])) {
                res += str1[--i];
            } else {
                res += str2[--j];
            }
        }
        std::ranges::reverse(res);

        return res;
    }
};