/*
 * 題目: https://leetcode.com/problems/sort-colors/description/
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
    void sortColors(std::vector<int> &nums) {
        int count[3] {0}, color = 0;

        for (int &n : nums) {
            ++count[n];
        }

        for (int i = 0, j = 0; i < 3; ++i) {
            while (count[color]--) {
                nums[j] = color;
                ++j;
            }
            ++color;
        }
    }
};

int main() {

    return 0;
}