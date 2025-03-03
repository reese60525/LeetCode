/*
 *  Author      : Reese
 *  Created On  : 2025-03-01 17:31
 *  Description : https://leetcode.com/problems/shift-distance-between-two-strings/description/
 */

#include <iostream>
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
    auto shiftDistance(std::string& s, std::string& t, std::vector<int>& nextCost,
                       std::vector<int>& previousCost) -> long long {
        long long leftShift[26], rightShift[26];

        leftShift[25] = previousCost[0];
        for (int i = 24; i > -1; --i) {
            leftShift[i] = leftShift[i + 1] + previousCost[i + 1];
        }

        rightShift[0] = nextCost[25];
        for (int i = 1; i < 26; ++i) {
            rightShift[i] = rightShift[i - 1] + nextCost[i - 1];
        }

        long long res = 0;
        for (int i = 0, len = s.size(); i < len; ++i) {
            int start = s[i] - 'a', end = t[i] - 'a';
            long long leftShiftCost, rightShiftCost;

            if (start < end) {
                leftShiftCost = leftShift[0] - leftShift[start] + leftShift[end];
                rightShiftCost = rightShift[end] - rightShift[start];
            } else {
                leftShiftCost = leftShift[end] - leftShift[start];
                rightShiftCost = rightShift[25] - rightShift[start] + rightShift[end];
            }

            res += std::min(leftShiftCost, rightShiftCost);
        }

        return res;
    }
};