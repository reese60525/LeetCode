/*
 *  Author      : Reese
 *  Created On  : 2025-03-03 09:19
 *  Description : https://leetcode.com/problems/partition-array-according-to-given-pivot
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
    std::vector<int> pivotArray(std::vector<int>& nums, int pivot) {
        int n = nums.size();
        std::vector<int> res(n, pivot);

        int l = 0, r = n - 1;
        for (int i = 0; i < n; ++i) {
            if (nums[i] < pivot) {
                res[l++] = nums[i];
            }
            if (nums[n - i - 1] > pivot) {
                res[r--] = nums[n - i - 1];
            }
        }

        return res;
    }
};