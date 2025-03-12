/*
 *  Author      : Reese
 *  Created On  : 2025-03-04 22:53
 *  Description : https://leetcode.com/problems/check-if-number-is-a-sum-of-powers-of-three
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
    static auto checkPowersOfThree(int& n) -> bool {
        int N = 16;
        int cnt = 0;
        while (--N >= 0) {
            cnt = static_cast<int>(std::pow(3, N));
            n -= n < cnt ? 0 : cnt;
        }

        return n == 0;
    }
};