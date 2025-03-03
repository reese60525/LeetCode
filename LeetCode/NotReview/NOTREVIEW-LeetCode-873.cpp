/*
 *  Author      : Reese
 *  Created On  : 2025-02-27 17:57
 *  Description : https://leetcode.com/problems/length-of-longest-fibonacci-subsequence/description/
 */

#include <iostream>
#include <unordered_map>
#include <vector>

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,abm,bmi2")

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    auto lenLongestFibSubseq(std::vector<int> &arr) -> int {
        int n = arr.size();
        int dp[n][n];
        std::unordered_map<int, int> numToIndex;

        std::memset(dp, 0, sizeof(dp));
        for (int i = 0; i < n; ++i) {
            numToIndex[arr[i]] = i;
        }

        int res = 0;
        for (int i = 1; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                int k = arr[j] - arr[i];
                auto it = numToIndex.find(k);
                if (it != numToIndex.end() && it->second < i) {
                    dp[i][j] = dp[it->second][i] + 1;
                    res = std::max(res, dp[i][j]);
                }
            }
        }

        return res == 0 ? 0 : res + 2;
    }
};