/*
 *  Author      : Reese
 *  Created On  : 2024-12-27 08:36
 *  Description : https://leetcode.com/problems/find-occurrences-of-an-element-in-an-array/description/
 */

#include <iostream>
#include <vector>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    std::vector<int> occurrencesOfElement(std::vector<int> &nums, std::vector<int> &queries, int x) {
        size_t x_cnt = 0; // x_cnt 表示 x 出現次數
        for (size_t i = 0; i < nums.size(); ++i) {
            if (nums[i] == x) {
                nums[x_cnt] = i; // 直接覆蓋 nums 重複利用空間
                ++x_cnt;
            }
        }

        for (size_t i = 0; i < queries.size(); ++i) {
            // 由於 nums 是從 0 開始存，nums[0] 表示 x 第一次出現的 index
            // 所以查找 nums 時 queries[i] 要 -1
            queries[i] = queries[i] > x_cnt ? -1 : nums[queries[i] - 1];
        }

        return queries;
    }
};

int main() {

    return 0;
}