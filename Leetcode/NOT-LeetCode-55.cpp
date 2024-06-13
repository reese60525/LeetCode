/*
 * 題目: https://leetcode.com/problems/jump-game/description/
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
    bool canJump(std::vector<int> &nums) {
        if (nums[0] == 0) {
            return false;
        }

        for (int i = nums.size() - 1; i > -1; --i) {
            if (nums[i] == 0) {
                while (i > 0 && nums[i] + 1 == nums[i - 1]) {
                    --i;
                }
                if (i == 0) {
                    return false;
                }
            }
        }

        return true;
    }
};

int main() {

    return 0;
}