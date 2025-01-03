/*
 *  Author      : Reese
 *  Created On  : 2025-01-03 08:07
 *  Description : https://leetcode.com/problems/number-of-ways-to-split-array/description/
 */

#include <iostream>
#include <numeric>
#include <vector>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    int waysToSplitArray(std::vector<int> &nums) {
        // total 會超出整數範圍，init 要用 0LL 表示 long long type 的 0
        long long total = std::accumulate(nums.begin(), nums.end(), 0LL);
        long long cur = 0;
        int res = 0;
        for (size_t i = 0; i < nums.size() - 1; ++i) {
            cur += nums[i];
            res += cur >= (total - cur);
        }

        return res;
    }
};

int main() {

    return 0;
}