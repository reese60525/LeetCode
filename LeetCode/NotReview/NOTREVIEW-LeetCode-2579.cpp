/*
 *  Author      : Reese
 *  Created On  : 2025-03-05 14:49
 *  Description : https://leetcode.com/problems/count-total-number-of-colored-cells
 */

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
    auto coloredCells(int n) -> long long {
        long long res = 1 + 4 * (static_cast<long long>(n) - 1) * n / 2;
        return res;
    }
};