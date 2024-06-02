/*
 * 題目: https://leetcode.com/problems/single-number/description/
 *
 * 題目解釋:
 *
 * 思路:
 *
 * 解法:
 *
 */
#include <iostream>

static const auto io_sync_off = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

class Solution {
  public:
    int singleNumber(std::vector<int> &nums) {

        for (int i = 1; i < nums.size(); ++i) {
            nums[i] ^= nums[i - 1];
        }
        return nums[nums.size() - 1];
    }
};

int main() {

    return 0;
}